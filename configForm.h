#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMainWindow>
#include <QPushButton>

#include "networkConfigForm.h"

class MainWindow;

class ConfigForm : public QDialog
{
public:
    ConfigForm(MainWindow* parent);
    ~ConfigForm();

    // Labels
    QLabel* gelbooruBasePathLabel =                 nullptr;
    QLabel* danboouBasePathLabel =                  nullptr;
    QLabel* r34BasePathLabel =                      nullptr;
    QLabel* animePicturesBasePathLabel =            nullptr;
    QLabel* yandereBasePathLabel =                  nullptr;
    QLabel* smtgbooruBasePathLabel =                nullptr;
    QLabel* gelbooruPageDefaultLabel =              nullptr;
    QLabel* danboorupageDefaultLabel =              nullptr;
    QLabel* danbooruNumDefaultLabel =               nullptr;
    QLabel* r34PageDefaultLabel =                   nullptr;
    QLabel* animePicturesPageDefaultLabel =         nullptr;
    QLabel* smtgbooruPageDefaultLabel =             nullptr;
    QLabel* danbooruKeyLabel =                      nullptr;
    QLabel* danbooruUserLabel =                     nullptr;
    QLabel* maxThreadsLabel =                       nullptr;
    QLabel* defaultServiceLabel =                   nullptr;

    // Input
    QLineEdit* gelbooruBasePath =                   nullptr;
    QLineEdit* danboouBasePath =                    nullptr;
    QLineEdit* r34BasePath =                        nullptr;
    QLineEdit* animePicturesBasePath =              nullptr;
    QLineEdit* yandereBasePath =                    nullptr;
    QLineEdit* smtgbooruBasePath =                  nullptr;
    QLineEdit* gelbooruPageDefault =                nullptr;
    QLineEdit* danboorupageDefault =                nullptr;
    QLineEdit* danbooruNumDefault =                 nullptr;
    QLineEdit* r34PageDefault =                     nullptr;
    QLineEdit* animePicturesPageDefault =           nullptr;
    QLineEdit* smtgbooruPageDefault =               nullptr;
    QPushButton* networkConfig =                    nullptr;
    QLineEdit* danbooruKey =                        nullptr;
    QLineEdit* danbooruUser =                       nullptr;
    QLineEdit* maxThreads =                         nullptr;
    QComboBox* defaultService =                     nullptr;

    // Accept/reject
    QDialogButtonBox* buttonBox =                   nullptr;

    // Grid layout for labels/input
    QGridLayout* mainLayout =                       nullptr;

    // Reference to main window
    MainWindow* mw =                                nullptr;

public:
    ///
    /// \brief acceptForm
    ///
    /// Takes ownership of passed pointer and deletes it
    ///
    /// Updates globals based on values stored in passed form
    ///
    /// \param netConfigForm
    ///
    void acceptForm(networkConfigForm* netConfigForm);

    ///
    /// \brief rejectForm
    ///
    /// Takes ownership of passed pointer and deletes it
    ///
    ///
    /// \param netConfigForm
    ///
    void rejectForm(networkConfigForm* netConfigForm);

    ///
    /// \brief newNetworkConfigForm
    /// Spawn new network config form
    ///
    ///
    void newNetworkConfigForm();


public slots:
    void verify();
    void reject();
};



#endif // CONFIGFORM_H
