import React, {Component} from 'react';


const electron = window.require('electron');
// const fs = electron.remote.require('fs');
const ipcRenderer  = electron.ipcRenderer;

class Main extends Component{
  constructor(props){
    super(props);
    this.state = {
      currentSong: {
        artist: null,
        id: null,
        name: null
      }
    }
    ipcRenderer.on('gcs', (event, arg) =>{
      console.log(arg);
    })
  }

  buttonPressed = () => {
    console.log("button accepted")
    console.log(ipcRenderer)
    ipcRenderer.send('gcs', 'hello')
  }

	render(){
    return(
      <div className = "loginMain">
      
        <button onClick={this.buttonPressed}> Hello! </button>
      </div>
    )
  }
}

export default Main;