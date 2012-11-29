/**
 * @file mainwindow.h
 * @brief The main window header class
 * @author SkyWodd & jordanVertaure
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This class is designed to handle all features of the music player.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section licence_sec Licence
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Phonon dependencies
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <phonon/BackendCapabilities>

// General purpose dependencies
#include <QMainWindow>
#include <QList>

// GUI dependencies
#include "ui_mainwindow.h"

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
protected:
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    QList<Phonon::MediaSource> sources;

protected slots:
    /**
     * Show the "add to playlist" popup menu
     *
     * @brief showAddMenu
     */
    void showAddMenu(void);

    /**
     * Remove the currently selected element in the playlist
     *
     * @brief removeElement
     */
    void removeElement(void);

    /**
     * Add a single file to the playlist
     *
     * @brief openFile
     */
    void openFile(void);

    /**
     * Change information of time
     *
     * @brief configure labels, buttons and slider when the media total time changed
     * @param totalTime total time of the media
     */
    void totalTimeChanged(qint64);

    /**
     * Scan a directory and add each readable files to the playlist
     *
     * @brief openDirectory
     */
    void openDirectory(void);

    /**
     * Open a playlist backup file
     *
     * @brief openPlaylist
     */
    void openPlaylist(void);

    /**
     * Save the current playlist to a file
     *
     * @brief savePlaylist
     */
    void savePlaylist(void);

    /**
     * Seek in the currently playing music stream
     *
     * @brief seekMusic
     * @param value The new seek value to apply
     */
    void seekMusic(const int value);

    /**
     * Change the volume of the output sound
     *
     * @brief changeVolume
     * @param value The new volume valu to apply
     */
    void changeVolume(const int value);

    /**
     * Play or pause current music stream
     *
     * @brief playPause
     */
    void playPause(void);

    /**
     * Stop the current music stream and go to the beginning of the playlist
     *
     * @brief stop
     */
    void stop(void);

    /**
     * Fast forward in the current music stream
     *
     * @brief fastForward
     */
    void fastForward(void);

    /**
     * Fast rewind in the current music stream
     *
     * @brief fastRewind
     */
    void fastRewind(void);

    /**
     * Start playing the next music file in the playlist
     *
     * @brief nextMusic
     */
    void nextMusic(void);

    /**
     * Start playing the previous music file in the playlist
     *
     * @brief previousMusic
     */
    void previousMusic(void);

    /**
     * Enable or disable random music playing
     *
     * @brief randomPlay
     */
    void randomPlay(void);

    /**
     * Show the "loop" popup menu
     *
     * @brief showLoopMenu
     */
    void showLoopMenu(void);

    /**
     * Enable or disable the loop playlist mode
     *
     * @brief loopPlaylist
     */
    void loopPlaylist(void);

    /**
     * Enable or disable the loop music mode
     *
     * @brief loopMusic
     */
    void loopMusic(void);

    void setAudioInterface(void); // TODO prototype

    /**
     * List available supported audio formats
     *
     * @brief listSupportedFormats
     */
    void listSupportedFormats(void);

    /**
     * List available audio output interfaces
     *
     * @brief listAvailableInterfaces
     */
    void listAvailableInterfaces(void);

    /**
     * Enable or disable the cover view
     *
     * @brief setPreview
     * @param state The new state of the cover view
     */
    void setPreview(const bool state = true);

    /**
     * Enable or disable the FFT view
     *
     * @brief setFFTview
     * @param state The new state of the FFT view
     */
    void setFFTview(const bool state = false);

    void processFFT(void); // TODO prototype

    /**
     * Show the help window
     *
     * @brief showManual
     */
    void showManual(void);

    /**
     * Show the "about" window
     *
     * @brief showAbout
     */
    void showAbout(void);

    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void timeTick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish(void);
    void tableDoubleClicked(int row, int column);
};

#endif // MAINWINDOW_H
