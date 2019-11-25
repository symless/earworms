import React,{ Component} from 'react';
// import logo from './logo.svg';
import './App.css';

const electron = window.require('electron');
const fs = electron.remote.require('fs');
const ipcRenderer  = electron.ipcRenderer;

class App extends Component{
  constructor(props){
    super(props);
    this.state = {}
    ipcRenderer.on('hello', (event, arg) =>{
      console.log(arg);
    })
  }

  buttonPressed = () => {
    ipcRenderer.send('hello', 'hiii')
  }

  render(){
    return(
      <div className = "loginMain">
        <script>
          window.require = require
        </script>
        <div className = "IP"> IP Address </div>
        <input type = "text"/>

        <div className = "name"> Name </div>
        <input type = "text"/>
      
        <button onClick={this.buttonPressed}> Hello! </button>
      </div>
    )
  }
}

export default App;
