const electron = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow

const path = require('path')

let mainWindow;

let connectionInfo = {
  host: '',
  port: 24825,
  pollFrequency: 1000
}

function createWindow() {
  // mainWindow = new BrowserWindow({ width: 350, height: 200, frame  : false })

  console.log("creating Window")
  const {net, ipcMain} = require('electron')

  mainWindow = new BrowserWindow({ 
    width: 411, 
    // width: 800, 
    height: 731, 
    frame: false,
    // frame: true,
    webPreferences: {
      nodeIntegration: true,
    }
  })

  // mainWindow.loadURL(`file://${path.join(__dirname, '../public/index.html')}`)
  mainWindow.loadURL('http://localhost:3000');
  mainWindow.setAlwaysOnTop(true)
  mainWindow.setResizable(false)
  mainWindow.on('closed', () => {
    mainWindow = null
  })

  ipcMain.on('gcs', (event, arg) => {


  ipcMain.on('set-connection-info', (event, args) => {
    console.log('Set Connection Info', args)
    connectionInfo = {
      ...connectionInfo,
      ...args
    };
    event.reply('get-connection-info', connectionInfo);
  })

  
  event.reply('hello', arg)

  const request = require('request');

  request({ 
          body: "", 
          followAllRedirects: true,
          headers: {
             'Content-Type': 'application/json',
          },
          method: 'GET',
          url: 'http://smaug:24825/songs/current'}, callback);

  function callback(error, response, body) {
      if (!error && response.statusCode == 200) {
          /// we send ipcRenderer the informaton
          console.log(body)
          jsonBody = JSON.parse(body)

          mainWindow.webContents.send('currentSong', jsonBody)


      } else {
          console.log("Error: \n"+body);
      }
  };




})
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
})