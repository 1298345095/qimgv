#include "documentinfo.h"

DocumentInfo::DocumentInfo(QString path)
    : mImageType(NONE),
      mOrientation(0),
      mExtension(nullptr)
{
    fileInfo.setFile(path);
    if(!fileInfo.isFile()) {
        qDebug() << "FileInfo: cannot open: " << path;
        return;
    }
    detectType();
    loadExifOrientation();
}

DocumentInfo::~DocumentInfo() {
}

// ##############################################################
// ####################### PUBLIC METHODS #######################
// ##############################################################

QString DocumentInfo::directoryPath() const {
    return fileInfo.absolutePath();
}

QString DocumentInfo::filePath() const {
    return fileInfo.absoluteFilePath();
}

QString DocumentInfo::fileName() const {
    return fileInfo.fileName();
}

QString DocumentInfo::baseName() const {
    return fileInfo.baseName();
}

// bytes
int DocumentInfo::fileSize() const {
    return static_cast<int>(fileInfo.size());
}

DocumentType DocumentInfo::type() const {
    return mImageType;
}

const char *DocumentInfo::extension() const {
    return mExtension;
}

QDateTime DocumentInfo::lastModified() const {
    return fileInfo.lastModified();
}

// For cases like orientation / even mimetype change we just reload
// Image from scratch, so don`t bother handling it here
void DocumentInfo::refresh() {
    fileInfo.refresh();
}

int DocumentInfo::exifOrientation() const {
    return mOrientation;
}

// ##############################################################
// ####################### PRIVATE METHODS ######################
// ##############################################################

// detect correct file extension
// TODO: this is just bad
void DocumentInfo::detectType() {
    QMimeDatabase mimeDb;
    QMimeType mimeType = mimeDb.mimeTypeForFile(fileInfo.filePath(), QMimeDatabase::MatchContent);
    QString mimeName = mimeType.name();

    if(mimeName == "video/webm") {
        mExtension = "webm";
        mImageType = DocumentType::VIDEO;
    } else if(mimeName == "video/mp4") {
        mExtension = "mp4";
        mImageType = DocumentType::VIDEO;
    } else if(mimeName == "image/jpeg") {
        mExtension = "jpg";
        mImageType = STATIC;
    } else if(mimeName == "image/png") {
        if(QImageReader::supportedImageFormats().contains("apng") && detectAPNG()) {
            mExtension = "apng";
            mImageType = ANIMATED;
        } else {
            mExtension = "png";
            mImageType = STATIC;
        }
    } else if(mimeName == "image/gif") {
        mExtension = "gif";
        mImageType = ANIMATED;
    // webp is incorrectly(?) detected as audio/x-riff on my windows pc
    } else if(mimeName == "audio/x-riff") {
        // in case we encounter an actual audio/x-riff
        if(QString::compare(fileInfo.completeSuffix(), "webp", Qt::CaseInsensitive) == 0) {
            mExtension = "webp";
            mImageType = detectAnimatedWebP() ? ANIMATED : STATIC;
        }
    // TODO: parse header to find out if it supports animation.
    // treat all webp as animated for now.
    } else if(mimeName == "image/webp") {
        mExtension = "webp";
        mImageType = detectAnimatedWebP() ? ANIMATED : STATIC;
    } else if(mimeName == "image/bmp") {
        mExtension = "bmp";
        mImageType = STATIC;
    } else {
        mExtension = fileInfo.completeSuffix().toStdString().c_str();
        mImageType = STATIC;
    }
}

inline
// dumb apng detector
bool DocumentInfo::detectAPNG() {
    QFile f(fileInfo.filePath());
    if(f.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&f);
        QString header(in.read(120)); // 120 chars should be sufficient?
        return header.contains("acTL");
    }
    return false;
}

bool DocumentInfo::detectAnimatedWebP() {
    QFile f(fileInfo.filePath());
    bool result = false;
    if(f.open(QFile::ReadOnly)) {
        QDataStream in(&f);
        in.skipRawData(12);
        char *buf = static_cast<char*>(malloc(5));
        buf[4] = '\0';
        in.readRawData(buf, 4);
        if(strcmp(buf, "VP8X") == 0) {
            in.skipRawData(4);
            char flags;
            in.readRawData(&flags, 1);
            if(flags & (1 << 1)) {
                result = true;
            }
        }
        free(buf);
    }
    return result;
}

void DocumentInfo::loadExifOrientation() {
    if(mImageType == VIDEO || mImageType == NONE)
        return;

    QString path = filePath();
    QImageReader *reader = nullptr;
    if(mExtension)
        reader = new QImageReader(path, mExtension);
    else
        reader = new QImageReader(path);

    if(reader->canRead())
        mOrientation = static_cast<int>(reader->transformation());
    delete reader;
}
