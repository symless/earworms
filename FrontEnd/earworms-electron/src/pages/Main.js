import React, {Component} from 'react';
import './Main.css';
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
        name: null,
        lengh: null,
        position: null,
      }
    }
    ipcRenderer.on('gcs', (event, arg) =>{
      console.log(arg);
    })

    ipcRenderer.on('currentSong', (event, arg) => {
      console.log(arg["artist"])
      this.state.currentSong = arg
      this.setState({currentSong : this.state.currentSong})
    })
  }

  buttonPressed = () => {
    ipcRenderer.send('gcs', 'hello')
  }

	render(){
    return(
      <div className = "displayMain">
        <script>
          window.require = require
        </script>
        <img className = "albumImage" src = "https://previews.123rf.com/images/aquir/aquir1311/aquir131100316/23569861-sample-grunge-red-round-stamp.jpg" />
        <div className = "bodyMain">
          <div className = "songDetailHolderMain">
            <div className = "songTitleMain">
              {this.state.currentSong.name}
            </div>
            <div className = "songArtistMain">
              {this.state.currentSong.artist}
            </div>
          </div>
          <div className = "buttonHolderMain">
            <button onClick={this.buttonPressed}>
              <img className = "buttonImg" src = {process.env.PUBLIC_URL + "/thumbs_down.png"}/>
            </button>
            <button onClick={this.buttonPressed}>
              <img className = "buttonImg" src = {process.env.PUBLIC_URL + "/thumbs_up.png"}/>
            </button>
          </div>
        </div>
      </div>
    );
  }
}

export default Main;