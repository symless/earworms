import React, { Component } from 'react';
import { Switch, Route, BrowserRouter as Router } from 'react-router-dom';

import './App.css';
import Settings from './pages/Settings';
import Main from './pages/Main';


class App extends Component{

  render(){
      <Router>
        <Switch>
          <Route path='/main' component={Main}/>
          <Route path='/' component={Settings} />
        </Switch>
      </Router>
    )
  }
}

export default App;
