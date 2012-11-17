#include "mainwindow.h"

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
    QObject::connect(this->music_fast_forward, SIGNAL(clicked()), this, SLOT(fastForward()));
    QObject::connect(this->music_fast_rewind, SIGNAL(clicked()), this, SLOT(fastRewind()));
    QObject::connect(this->music_next, SIGNAL(clicked()), this, SLOT(nextMusic()));
    QObject::connect(this->music_previous, SIGNAL(clicked()), this, SLOT(previousMusic()));
    QObject::connect(this->music_random_play, SIGNAL(clicked()), this, SLOT(randomPlay()));
    QObject::connect(this->music_loop_play, SIGNAL(clicked()), this, SLOT(showLoopMenu()));

    // Connect playlist buttons signals to slots
    QObject::connect(this->playlist_add, SIGNAL(clicked()), this, SLOT(showAddMenu()));
    QObject::connect(this->playlist_remove, SIGNAL(clicked()), this, SLOT(removeElement()));
    QObject::connect(this->playlist_save, SIGNAL(clicked()), this, SLOT(savePlaylist()));
    QObject::connect(this->playlist_load, SIGNAL(clicked()), this, SLOT(openPlaylist()));

    // Connect others signals to slots
}

MainWindow::~MainWindow()
{
}

void MainWindow::showAddMenu()
{
}

void MainWindow::openFile(void)
{
}

void MainWindow::openDirectory()
{
}

void MainWindow::openPlaylist()
{
}

void MainWindow::savePlaylist()
{
}

void MainWindow::seekMusic()
{
}

void MainWindow::changeVolume()
{
}

void MainWindow::playPause()
{
}

void MainWindow::stop()
{
}

void MainWindow::fastForward()
{
}

void MainWindow::fastRewind()
{
}

void MainWindow::nextMusic()
{
}

void MainWindow::previousMusic()
{
}

void MainWindow::randomPlay()
{
}

void MainWindow::showLoopMenu()
{
}

void MainWindow::loopPlaylist()
{
}

void MainWindow::loopMusic()
{
}

void MainWindow::setAudioInterface()
{
}

void MainWindow::listSupportedFormats()
{
}

void MainWindow::listAvailableInterfaces()
{
}

void MainWindow::setPreview(const bool state)
{
}

void MainWindow::setFFTview(const bool state)
{
}

void MainWindow::processFFT()
{
}

void MainWindow::showManual()
{
}

void MainWindow::showAbout()
{
}

void MainWindow::removeElement()
{
}
