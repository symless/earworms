const electron = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow

const path = require('path')

let mainWindow

function createWindow() {
  // mainWindow = new BrowserWindow({ width: 350, height: 200, frame  : false })

  console.log("creating Window")
  const {net, ipcMain} = require('electron')

  mainWindow = new BrowserWindow({ 
    width: 350, 
    height: 200, 
    // frame: false,
    frame: true,
    webPreferences: {
      nodeIntegration: true,
    }
  })

  // mainWindow.loadURL(`file://${path.join(__dirname, '../public/index.html')}`)
  mainWindow.loadURL('http://localhost:3000');
  mainWindow.setAlwaysOnTop(true)
  // mainWindow.setResizable(false)
  mainWindow.on('closed', () => {
    mainWindow = null
  })

  ipcMain.on('gcs', (event, arg) => {
  console.log("got something")
  event.reply('hello', arg)

  const request = require('request');

  request({ 
          body: "", 
          followAllRedirects: true,
          headers: {
             'Content-Type': 'application/json',
          },
          method: 'POST',
          url: 'http://pathofexile.com/api/trade/search/Incursion'}, callback);

  function callback(error, response, body) {
      if (!error && response.statusCode == 200) {
          console.log('Success: \n'+body);
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