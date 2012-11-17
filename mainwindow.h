#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <phonon/BackendCapabilities>
#include <QMainWindow>
#include <QList>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    QList<Phonon::MediaSource*> sources;

public slots:
    void showAddMenu(void);
    void removeElement(void);
    void openFile(void);
    void openDirectory(void);
    void openPlaylist(void);
    void savePlaylist(void);
    void seekMusic(void);
    void changeVolume(void);
    void playPause(void);
    void stop(void);
    void fastForward(void);
    void fastRewind(void);
    void nextMusic(void);
    void previousMusic(void);
    void randomPlay(void);
    void showLoopMenu(void);
    void loopPlaylist(void);
    void loopMusic(void);
    void setAudioInterface(void); // TODO prototype
    void listSupportedFormats(void);
    void listAvailableInterfaces(void);
    void setPreview(const bool state = true);
    void setFFTview(const bool state = false);
    void processFFT(void); // TODO prototype
    void showManual(void);
    void showAbout(void);
};

#endif // MAINWINDOW_H
