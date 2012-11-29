/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 *
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 *
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

// Includes
#include <iostream>
#include <QMessageBox>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QDesktopServices>
#include <QStringList>
#include <QString>
#include <QTime>
#include <QIcon>
#include "mainwindow.h"
#include "ui_about.h"

#define play_icon QIcon("icons/play_music.png")
#define pause_icon QIcon("icons/pause_music.png")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Setup Ui
    setupUi(this);

    // Connect menu signals to slots
    QObject::connect(this->action_open_file, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(this->action_open_directory, SIGNAL(triggered()), this, SLOT(openDirectory()));
    QObject::connect(this->action_open_playlist, SIGNAL(triggered()), this, SLOT(openPlaylist()));
    QObject::connect(this->action_save_playlist, SIGNAL(triggered()), this, SLOT(savePlaylist()));
    QObject::connect(this->action_play_pause, SIGNAL(triggered()), this, SLOT(playPause()));
    QObject::connect(this->action_stop, SIGNAL(triggered()), this, SLOT(stop()));
    QObject::connect(this->action_fast_forward, SIGNAL(triggered()), this, SLOT(fastForward()));
    QObject::connect(this->action_fast_rewind, SIGNAL(triggered()), this, SLOT(fastRewind()));
    QObject::connect(this->action_next_music, SIGNAL(triggered()), this, SLOT(nextMusic()));
    QObject::connect(this->action_previous_music, SIGNAL(triggered()), this, SLOT(previousMusic()));
    QObject::connect(this->action_random_play, SIGNAL(triggered()), this, SLOT(randomPlay()));
    QObject::connect(this->action_loop_music, SIGNAL(triggered()), this, SLOT(loopMusic()));
    QObject::connect(this->action_loop_playlist, SIGNAL(triggered()), this, SLOT(loopPlaylist()));
    QObject::connect(this->action_enable_fft, SIGNAL(triggered(bool)), this, SLOT(setFFTview(bool)));
    QObject::connect(this->action_enable_preview, SIGNAL(triggered(bool)), this, SLOT(setPreview(bool)));
    QObject::connect(this->action_manual, SIGNAL(triggered()), this, SLOT(showManual()));
    QObject::connect(this->action_about, SIGNAL(triggered()), this, SLOT(showAbout()));

    // Connect controls buttons signals to slots
    QObject::connect(this->music_play_pause, SIGNAL(clicked()), this, SLOT(playPause()));
    QObject::connect(this->music_stop, SIGNAL(clicked()), this, SLOT(stop()));
    QObject::connect(this->music_fast_forward, SIGNAL(pressed()), this, SLOT(fastForward()));
    QObject::connect(this->music_fast_rewind, SIGNAL(pressed()), this, SLOT(fastRewind()));
    QObject::connect(this->music_next, SIGNAL(clicked()), this, SLOT(nextMusic()));
    QObject::connect(this->music_previous, SIGNAL(clicked()), this, SLOT(previousMusic()));
    QObject::connect(this->music_random_play, SIGNAL(clicked()), this, SLOT(randomPlay()));
    QObject::connect(this->music_loop_play, SIGNAL(clicked()), this, SLOT(showLoopMenu()));

    // Connect playlist buttons signals to slots
    QObject::connect(this->playlist_add, SIGNAL(clicked()), this, SLOT(showAddMenu()));
    QObject::connect(this->playlist_remove, SIGNAL(clicked()), this, SLOT(removeElement()));
    QObject::connect(this->playlist_save, SIGNAL(clicked()), this, SLOT(savePlaylist()));
    QObject::connect(this->playlist_load, SIGNAL(clicked()), this, SLOT(openPlaylist()));

    // Connect sliders signals to slots
    QObject::connect(this->music_time_slide, SIGNAL(valueChanged(int)), this, SLOT(seekMusic(int)));
    QObject::connect(this->music_volume_slide, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));

    // Instantiate Phonon objetcs
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);

    // Setup tick interval
    mediaObject->setTickInterval(1000);

    // Connect Phonon signals to slots
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(timeTick(qint64)));
    connect(mediaObject, SIGNAL(totalTimeChanged(qint64)), this, SLOT(totalTimeChanged(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    // Connect media object to the audio output
    Phonon::createPath(mediaObject, audioOutput);

}

MainWindow::~MainWindow(void)
{
    // Free memory
    delete audioOutput;
    delete mediaObject;
    delete metaInformationResolver;
}

void MainWindow::showAddMenu(void)
{
}

void MainWindow::openFile(void)
{
    // Drop QFileDialog
    QStringList filenames = QFileDialog::getOpenFileNames(this, QString("Ajouter des fichiers"),
                                                          QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    // Check if user as selected at least one file
    if (filenames.isEmpty())
        return;

    // Get the current playlist size
    int index = sources.size();

    // For each selected files
    foreach (QString string, filenames) {

        // Open file and add it to the playlist
        Phonon::MediaSource source(string);
        sources.append(source);
    }

    //
    if (!sources.isEmpty()) {
        metaInformationResolver->setCurrentSource(sources.at(index));

        //Set the first source ready to be read
        mediaObject->setCurrentSource(sources.front());

        //if there is more than one music opened
        if(sources.size()>1){
            music_next->setEnabled(true);
            music_previous->setEnabled(true);
        }

        //Enable labels
        music_time_elapse_label->setEnabled(true);
        music_volume_label->setEnabled(true);

        //Enable buttons
        music_play_pause->setEnabled(true);
        music_stop->setEnabled(true);
        music_time_slide->setEnabled(true);
        music_volume_slide->setEnabled(true);

    }
}

void MainWindow::totalTimeChanged(qint64 totalTime)
{
    //Display Time
    QTime displayTime(0, (totalTime / 60000) % 60, (totalTime / 1000) % 60);
    music_time_total_label->setText(displayTime.toString("mm:ss"));

    //Configure sliders
    music_time_slide->setMaximum(totalTime/1000);

    //Enable labels
    music_time_total_label->setEnabled(true);

    //Enable buttons
    music_fast_forward->setEnabled(true);
    music_fast_rewind->setEnabled(true);

    //Enable sliders
    music_time_slide->setEnabled(true);
    music_volume_slide->setEnabled(true);
}

void MainWindow::openDirectory(void)
{
}

void MainWindow::openPlaylist(void)
{
}

void MainWindow::savePlaylist(void)
{
}

void MainWindow::seekMusic(const int value)
{
    if(value*1000!=mediaObject->currentTime())
        mediaObject->seek(value*1000);
}

void MainWindow::changeVolume(const int value)
{
    audioOutput->setVolume(qreal(value)/music_volume_slide->maximum());
    QString valueText = QString::number(value);
    music_volume_label->setText(valueText);
}

void MainWindow::playPause(void)
{
    if(mediaObject->state()==Phonon::PlayingState)
        //pause
        mediaObject->pause();
    else
        //play
        mediaObject->play();

}

void MainWindow::stop(void)
{
    mediaObject->stop();
    QTime displayTime(0, 0, 0);
    music_time_elapse_label->setText(displayTime.toString("mm:ss"));
    music_time_slide->setValue(0);

}

void MainWindow::fastForward(void)
{
}

void MainWindow::fastRewind(void)
{
}

void MainWindow::nextMusic(void)
{
}

void MainWindow::previousMusic(void)
{
}

void MainWindow::randomPlay(void)
{
}

void MainWindow::showLoopMenu(void)
{
}

void MainWindow::loopPlaylist(void)
{
}

void MainWindow::loopMusic(void)
{
}

void MainWindow::setAudioInterface(void)
{
}

void MainWindow::listSupportedFormats(void)
{
}

void MainWindow::listAvailableInterfaces(void)
{
}

void MainWindow::setPreview(const bool state)
{
}

void MainWindow::setFFTview(const bool state)
{
}

void MainWindow::processFFT(void)
{
}

void MainWindow::showManual(void)
{
    QMessageBox::information(this, QString("User manual"), QString("Sorry guy, I'm too lazy to write this help guide :)"));
}

void MainWindow::showAbout(void)
{
    QDialog about_window;
    Ui::about_dialog about;
    about.setupUi(&about_window);
    about_window.exec();
}

void MainWindow::stateChanged(Phonon::State newState, Phonon::State oldState)
{
    switch (newState) {
    case Phonon::ErrorState:
        if (mediaObject->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("Fatal Error"),
                                 mediaObject->errorString());
        } else {
            QMessageBox::warning(this, tr("Error"),
                                 mediaObject->errorString());
        }
        break;
    case Phonon::PlayingState:
        music_play_pause->setIcon(pause_icon);
        break;
    case Phonon::StoppedState:
         music_play_pause->setIcon(play_icon);
        break;
    case Phonon::PausedState:
        music_play_pause->setIcon(play_icon);
        break;
    case Phonon::BufferingState:
        // TODO
        break;
    default:
        ;
    }
}

void MainWindow::timeTick(qint64 time)
{
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    music_time_elapse_label->setText(displayTime.toString("mm:ss"));
    music_time_slide->setValue(time/1000);
}

void MainWindow::sourceChanged(const Phonon::MediaSource &source)
{
}

void MainWindow::metaStateChanged(Phonon::State newState, Phonon::State oldState)
{
}

void MainWindow::aboutToFinish(void)
{
}

void MainWindow::tableDoubleClicked(int row, int column)
{
}

void MainWindow::removeElement(void)
{
}
