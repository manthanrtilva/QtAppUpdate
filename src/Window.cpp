/*
 * Copyright (c) 2014-2016 Alex Spataru <alex_spataru@outlook.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#include "Window.h"
#include "ui_Window.h"

#include <QSimpleUpdater.h>
#include <iostream>

//==============================================================================
// Define the URL of the Update Definitions file
//==============================================================================

static const QString DEFS_URL = "http://localhost/updates.json";

//==============================================================================
// Window::Window
//==============================================================================

Window::Window(QWidget *parent) : QMainWindow(parent) {
  m_ui = new Ui::Window;
  m_ui->setupUi(this);
  m_ui->label->setText(QString("Version:%1").arg(PROJECT_VERSION));

  setWindowTitle(qApp->applicationName());

  /* QSimpleUpdater is single-instance */
  m_updater = QSimpleUpdater::getInstance();

  /* Check for updates when the "Check For Updates" button is clicked */
  connect(m_updater, SIGNAL(checkingFinished(QString)), this,
          SLOT(updateChangelog(QString)));
  // connect (m_updater, SIGNAL (appcastDownloaded (QString, QByteArray)),
  //          this,        SLOT (displayAppcast    (QString, QByteArray)));
  m_pleasewait = new QProgressDialog(this);
  m_pleasewait->setLabelText("Please wait");
  m_pleasewait->setMinimum(0);
  m_pleasewait->setMaximum(0);
  m_pleasewait->setCancelButton(nullptr);
}

//==============================================================================
// Window::~Window
//==============================================================================

Window::~Window() { delete m_ui; }

//==============================================================================
// Window::checkForUpdates
//==============================================================================

// void Window::resetFields()
// {
//     // m_ui->installedVersion->setText ("0.1");
//     // m_ui->customAppcast->setChecked (false);
//     // m_ui->enableDownloader->setChecked (true);
//     // m_ui->showAllNotifcations->setChecked (false);
//     // m_ui->showUpdateNotifications->setChecked (true);
// }
//
//==============================================================================
// Window::checkForUpdates
//==============================================================================

void Window::checkForUpdates() {
  // /* Apply the settings */
  // m_updater->setModuleVersion (DEFS_URL, PROJECT_VERSION);
  // m_updater->setNotifyOnFinish (DEFS_URL, false);
  // m_updater->setNotifyOnUpdate (DEFS_URL, true);
  // m_updater->setUseCustomAppcast (DEFS_URL, false);
  // m_updater->setDownloaderEnabled (DEFS_URL, true);

  /* Check for updates */
  m_updater->checkForUpdates(DEFS_URL);
}

//==============================================================================
// Window::updateChangelog
//==============================================================================

void Window::updateChangelog(const QString &url) {
  std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
  m_pleasewait->reset();
  // if (url == DEFS_URL)
  //     m_ui->changelogText->setText (m_updater->getChangelog (url));
}

//==============================================================================
// Window::displayAppcast
//==============================================================================

// void Window::displayAppcast (const QString& url, const QByteArray& reply)
// {
//     if (url == DEFS_URL) {
//         QString text = "This is the downloaded appcast: <p><pre>" +
//                        QString::fromUtf8 (reply) +
//                        "</pre></p><p> If you need to store more information
//                        on the " "appcast (or use another format), just use
//                        the "
//                        "<b>QSimpleUpdater::setCustomAppcast()</b> function. "
//                        "It allows your application to interpret the appcast "
//                        "using your code and not QSU's code.</p>";
//
//         // m_ui->changelogText->setText (text);
//     }
// }
void Window::showEvent(QShowEvent *ev) {
  QMainWindow::showEvent(ev);
  if (m_isFirstTime) {
    std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
    m_pleasewait->open(nullptr, nullptr);
    std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
    checkForUpdates();
    std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
    m_isFirstTime = false;
  }
  // m_pleasewait->done(0);
}
