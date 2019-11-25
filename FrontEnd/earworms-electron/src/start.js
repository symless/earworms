const electron = require('electron')
const {ipcMain} = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow

const path = require('path')

let mainWindow

function createWindow() {
  // mainWindow = new BrowserWindow({ width: 350, height: 200, frame  : false })
  mainWindow = new BrowserWindow({ 
    width: 350, 
    height: 200, 
    frame: false,
    webPreferences: {
      nodeIntegration: true,
    }
  })

  // mainWindow.loadURL(`file://${path.join(__dirname, '../public/index.html')}`)
  mainWindow.loadURL('http://localhost:3000');
  mainWindow.setAlwaysOnTop(true)
  mainWindow.setResizable(false)
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

ipcMain.on('hello', (event, arg) => {
  event.reply('hello', arg)
})