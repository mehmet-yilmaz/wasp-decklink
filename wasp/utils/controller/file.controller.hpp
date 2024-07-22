#ifndef ___WASP_UTILS_FILE_CONTROLLER_HPP___
#define ___WASP_UTILS_FILE_CONTROLLER_HPP___

#include <types/content-type.enum.hpp>

namespace Wasp
{
    namespace Controllers
    {
        class FileController
        {
        public:
            static bool isExist(const std::string &path)
            {
                struct stat buffer;
                return (stat(path.c_str(), &buffer) == 0);
            };

            static std::unique_ptr<std::string> getExtention(const std::string &filename)
            {
                if (filename.find_last_of(".") != std::string::npos)
                    return std::make_unique<std::string>(filename.substr(filename.find_last_of(".") + 1));
                else
                    return nullptr;
            }

            static std::vector<std::string> splitString(const std::string &path, const char &delimeter)
            {
                std::vector<std::string> result;
                std::istringstream stream(path);
                std::string token;
                while (std::getline(stream, token, delimeter))
                {
                    result.push_back(token);
                }
                return result;
            };

            static std::unique_ptr<std::pair<Wasp::Types::EContentType, std::string>> getContentType(const std::string &extention)
            {

                if (extention == "html" || extention == "htm" || extention == "shtml")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextHTML, "text/html"));
                if (extention == "xhtml")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXHTMLXML, "application/xhtml+xml"));
                if (extention == "css")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextCSS, "text/css"));
                if (extention == "js")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXJAVASCRIPT, "application/x-javascript"));
                if (extention == "png")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImagePNG, "image/png"));
                if (extention == "gif")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageGIF, "image/gif"));
                if (extention == "jpeg" || extention == "jpg")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageJPEG, "image/jpeg"));
                if (extention == "svg")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageSVGXML, "image/svg+xml"));
                if (extention == "ico")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageXICON, "image/x-icon"));
                if (extention == "txt")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextPLAIN, "text/plain"));
                if (extention == "xml")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextXML, "text/xml"));
                if (extention == "mml")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextMATHML, "text/mathml"));
                if (extention == "jad")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextVNDSUNJ2MEAPPDESCRIPTOR, "text/vnd.sun.j2me.app-descriptor"));
                if (extention == "wml")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextVNDWAPWML, "text/vnd.wap.wml"));
                if (extention == "htc")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::TextXCOMPONENT, "text/x-component"));
                if (extention == "webp")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageWEBP, "image/webp"));
                if (extention == "mp4" || extention == "m4v")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoMP4, "video/mp4"));
                if (extention == "mpeg" || extention == "mpg")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoMPEG, "video/mpeg"));
                if (extention == "mov")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoQUICKTIME, "video/quicktime"));
                if (extention == "flv")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoXFLV, "video/x-flv"));
                if (extention == "wmv")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoXMSWMV, "video/x-ms-wmv"));
                if (extention == "avi")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoXMSVIDEO, "video/x-msvideo"));
                if (extention == "mp3")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::AudioMPEG, "audio/mpeg"));
                if (extention == "ogg")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::AudioOGG, "audio/ogg"));
                if (extention == "3gpp" || extention == "3gp")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::Video3GPP, "video/3gpp"));
                if (extention == "atom")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationATOMXML, "application/atom+xml"));
                if (extention == "rss")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationRSSXML, "application/rss+xml"));
                if (extention == "wbmp")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageVNDWAPWBMP, "image/vnd.wap.wbmp"));
                if (extention == "jng")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ImageXJNG, "image/x-jng"));
                if (extention == "jar" || extention == "war" || extention == "ear")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationJAVAARCHIVE, "application/java-archive"));
                if (extention == "hqx")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationMACBINHEX40, "application/mac-binhex40"));
                if (extention == "doc")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationMSWORD, "application/msword"));
                if (extention == "pdf")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationPDF, "application/pdf"));
                if (extention == "ps" || extention == "eps" || extention == "ai")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationPOSTSCRIPT, "application/postscript"));
                if (extention == "rtf")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationRTF, "application/rtf"));
                if (extention == "xls")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationVNDMSEXCEL, "application/vnd.ms-excel"));
                if (extention == "ppt")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationVNDMSPPT, "application/vnd.ms-powerpoint"));
                if (extention == "wmlc")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationVNDWAPWMLC, "application/vnd.wap.wmlc"));
                if (extention == "kml")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationVNDGOOGLEEARTHKMLXML, "application/vnd.google-earth.kml+xml"));
                if (extention == "kmz")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationVNDGOOGLEEARTHKMZ, "application/vnd.google-earth.kmz"));
                if (extention == "7z")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationX7ZCOMPRESSED, "application/x-7z-compressed"));
                if (extention == "cco")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXCOCOA, "application/x-cocoa"));
                if (extention == "jardiff")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXJAVAARCHIVEDIFF, "application/x-java-archive-diff"));
                if (extention == "jnlp")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXJAVAJNLPFILE, "application/x-java-jnlp-file"));
                if (extention == "run")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXMAKESELF, "application/x-makeself"));
                if (extention == "pl" || extention == "pm")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXPEARL, "application/x-pearl"));
                if (extention == "prc" || extention == "pdb")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXPILOT, "application/x-pilot"));
                if (extention == "rar")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXRARCOMPRESSED, "application/x-rar-compressed"));
                if (extention == "rpm")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXREDHATPACKAGEMANAGER, "application/x-redhat-package-manager"));
                if (extention == "sea")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXSEA, "application/x-sea"));
                if (extention == "swf")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXSHOCKWAVEFLASH, "application/x-shockwave-flash"));
                if (extention == "sit")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXSTUFFIT, "application/x-stuffit"));
                if (extention == "tcl" || extention == "tk")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXTCL, "application/x-tcl"));
                if (extention == "der" || extention == "pem" || extention == "crt")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXX509CACERT, "application/x-x509-ca-cert"));
                if (extention == "xpi")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationXPINSTALL, "application/x-xpinstall"));
                if (extention == "zip")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationRSSXML, "application/zip"));
                if (extention == "bin" || extention == "exe" || extention == "dll" || extention == "deb" || extention == "dmg" || extention == "eot" || extention == "iso" || extention == "img" || extention == "msi" || extention == "msp" || extention == "msm")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::ApplicationOCTETSTREAM, "application/octet-stream"));
                if (extention == "mid" || extention == "midi" || extention == "kar")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::AudioMIDI, "audio/midi"));
                if (extention == "ra")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::AudioXREALAUDIO, "audio/x-realaudio"));
                if (extention == "mng")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoXMNG, "video/x-mng"));
                if (extention == "asx" || extention == "asf")
                    return std::make_unique<std::pair<Wasp::Types::EContentType, std::string>>(std::make_pair<Wasp::Types::EContentType, std::string>(Wasp::Types::EContentType::VideoXMSASF, "video/x-ms-asf"));
                return nullptr;
            }
        };
    }
}

#endif // !___WASP_UTILS_FILE_CONTROLLER_HPP___