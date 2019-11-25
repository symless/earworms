const electron = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow

const path = require('path')

let mainWindow

function createWindow() {
  mainWindow = new BrowserWindow({ width: 800, height: 600 })

  mainWindow.loadURL(`file://${path.join(__dirname, '../public/index.html')}`)

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