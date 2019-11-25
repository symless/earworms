import React, {Component} from 'react';
import {Redirect} from 'react-router-dom';

class Settings extends Component {
    constructor() {
        super();
        this.state = {shouldRedirect: false};
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleSubmit() {
        this.setState({shouldRedirect: true})
    }

    render() {
        const {shouldRedirect} = this.state;
        if (shouldRedirect) {
            return (<Redirect to='/main'/>);
        } else {
            return (
                <div>
                    <div className = "IP address"> IP Address </div>
                    <input type = "text"/>
        
                    <div className = "IP address"> Name </div>
                    <input type = "text"/>
        
                    <button type='button' onClick={this.handleSubmit}>Save</button>
        
                </div>
            );
        }
    }
}

export default Settings;