const electron = require('electron')
const {ipcMain} = require('electron')
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
  mainWindow = new BrowserWindow({ 
    width: 350, 
    height: 600, 
    frame: true,
    webPreferences: {
      nodeIntegration: true,
    }
  })

  // mainWindow.loadURL(`file://${path.join(__dirname, '../public/index.html')}`)
  mainWindow.loadURL('http://localhost:3000');
  mainWindow.setAlwaysOnTop(true)
  mainWindow.setResizable(true)
  // mainWindow.removeMenu()
  // mainWindow.setMenuBarVisibility(false)
  mainWindow.on('closed', () => {
    mainWindow = null
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

ipcMain.on('set-connection-info', (event, args) => {
  console.log('Set Connection Info', args)
  connectionInfo = {
    ...connectionInfo,
    ...args
  };
  event.reply('get-connection-info', connectionInfo);
})

ipcMain.on('hello', (event, arg) => {
  event.reply('hello', arg)
})