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

  const request = net.request({
    method:'GET',
    protocol:'https:',
    hostname:'github.com',
    port: 443,
    path: '/'
  })

  request.on('response', (response) => {
    console.log(response);
    response.on('error', (error) => {
      console.log('Error: ${JSON.stringify(error)}')
    })
  })

  request.on('login', (authInfo, callBack) => {
    console.log("LOGIN")
    console.log(authInfo)
    console.log(callBack)
  })


  ipcMain.on('gcs', (event, arg) => {
  console.log("got something")
  event.reply('hello', arg)
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