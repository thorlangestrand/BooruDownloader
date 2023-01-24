#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <future>

#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QMessageBox>


#include "nlohmann_json.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servicesEnums.hpp"

#include <QDebug>

// parsed index, basepath (ex: D:\\images\\), currentImage current index within json block, selectedService int value representing each service
// 0 = Gelbooru
// 1 = Danbooru
void downloadImage(nlohmann::json parsedIndex, QString basePath, int currentPage, int currentImage, int selectedService)
{
    // This block parses the individual images of the blocks passed from main
    std::stringstream idStream;
    idStream << parsedIndex.at("id");
    QString id = QString::fromStdString(idStream.str());


    std::stringstream urlStream;
    urlStream << parsedIndex.at("file_url");


    std::string urlString = urlStream.str();
    urlString = urlString.substr(1, urlString.size() - 2);

    std::string fileExtension = urlString.substr(urlString.size() - 3, urlString.size());

    QString pathExtension = "";

    if (fileExtension == "peg" || fileExtension == "jpg" || fileExtension == "png")
    {
        pathExtension = ".png";
    }
    else if (fileExtension == "gif")
    {
        pathExtension = ".gif";
    }
    else if (fileExtension == "mp4" || fileExtension == "ebm")
    {
        pathExtension = ".mp4";
    }
    // If it doesn't match any of these it's the cursed fucking danbooru format (#｀-_ゝ-)
    else
    {
        if (selectedService == Services::Danbooru)
        {
            pathExtension = ".mp4";
            urlStream.str("");
            urlStream.clear();
            urlStream << parsedIndex.at("large_file_url");
            urlString = urlStream.str();
            urlString = urlString.substr(1, urlString.size() - 2);
        }
        else if (selectedService == Services::Gelbooru)
        {
            pathExtension = ".mp4";
        }
    }

    QNetworkAccessManager *man = new QNetworkAccessManager;

    // On QNetworkAccessManager::finished call MainWindow::imageDownloader with return value of QNetworkAccessManager::finished
    // Ok holy shit i finally understand it
    //connect(man, &QNetworkAccessManager::finished, this, &MainWindow::downloadIndividual);



    QEventLoop loop;


    QObject::connect(man, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    const QUrl url(QString::fromStdString(urlString));
    QNetworkRequest request(url);
    //man->get(request);
    QNetworkReply *reply = man->get((request));
    loop.exec();

    QByteArray bits = reply->readAll();

    std::stringstream h;
    h << currentImage;
    QString d = QString::fromStdString(h.str());

    std::stringstream g;
    g << currentPage;
    QString k = QString::fromStdString(g.str());



    // basePath, e.g. D:/images/gelboorucpp/league_of_legends
    // spacer
    QString fullPath = basePath + k + " " + d + " " + id + pathExtension;

    QFile file(fullPath);

    file.open(QIODevice::WriteOnly);
    file.write(bits);
    file.close();

    delete reply;
    delete man;
}



void MainWindow::imageDownloader(QNetworkReply *reply, int pageNum)
{
    // This block parses the individual blocks passed from main



    // Raw body data
    QByteArray raw = reply->readAll();
    // Convert to standard string
    std::string sStandardString = raw.toStdString();

    qDebug() << sStandardString.c_str();
    
    nlohmann::json parsed;
    switch(MainWindow::selected)
    {
    case Services::Gelbooru: {
        // This is bad code. Will I ever fix it? If this comment is still here that means it worked
        //qDebug() << QString::fromStdString(sStandardString);
        nlohmann::json parsedJson= nlohmann::json::parse(sStandardString);
        std::stringstream ss;

        
        // If no post (there is no post block if there are no posts)
        // then need to expect and catch the error otherwise it will crash the program
        try {
            ss << parsedJson.at("post");
        }  catch (const std::exception& e) {
           break;
        }
        
        parsed = nlohmann::json::parse(ss.str());
        
        // Use dump to convert between nlohmann json objects and std::string objects
        // that can then be further processed using qt tools
        //qDebug() << QString::fromStdString(parsed.dump());
        break;
    }
    default: {
        // Converted to JSON to be further processed
        parsed = nlohmann::json::parse(sStandardString);
        break;
    }
    }

    // Create Folder if valid response

    if (parsed.size() == 0)
    {
        // Uncomment this block for annoying messages

        //QMessageBox box;
        //box.setWindowTitle("No results");
        //box.setText("No results returned for\nparsed tags");
        //box.exec();
        //QMessageBox::information(this, "No res","No results for given \nsearch terms");

        // Reset Search

        return;
    }

    QDir dir(MainWindow::filePath);
    if (!dir.exists())
    {
        dir.mkdir(MainWindow::filePath);
    }


    int selectedService = selected;

    std::vector<std::future<void>> img_futures;


    for(ulong i = 0; i < parsed.size(); i++)
    {
        img_futures.push_back(std::async(std::launch::async, downloadImage, parsed[i], MainWindow::filePath, pageNum, i, selectedService));
    }

    for (ulong i = 0; i < img_futures.size(); i++)
    {
        img_futures[i].wait();
    }

    reply->deleteLater();

}






