/*
 *  OscSender.cpp
 *  openTSPS
 */

#include "ofxTSPS/person/Person.h"
#include "ofxTSPS/communication/OscSender.h"

namespace ofxTSPS {
    
    /***************************************************************
     CONSTRUCTOR + SETUP
     ***************************************************************/
    
    OscSender::OscSender(){
        useLegacy = false;
    };
    
    OscSender::OscSender(string _ip, int _port){
        setupSender(_ip, _port);
    };
    
    void OscSender::setupSender(string _ip, int _port){
        ip = oldip = _ip;
        port = oldport = _port;
        
        stringstream message;
        message<<"SETTING UP SENDER @ "<<ip<<":"<<port;
        ofLog(OF_LOG_VERBOSE, message.str());
        
        setup(ip, port);
    };
    
    /***************************************************************
     UPDATE
     ***************************************************************/
    
    void OscSender::update(){
        if (strcmp(oldip.c_str(), ip.c_str()) != 0 || oldport != port){
            oldip = ip;
            oldport = port;
            reroute(ip, port);				
        }
    }
    
    /***************************************************************
     SEND
     ***************************************************************/
    
    
    void OscSender::personEntered ( Person * p, ofPoint centroid, int cameraWidth, int cameraHeight, bool bSendContours ){
        string message = useLegacy ? "TSPS/personEntered/" : "/TSPS/personEntered/"; 
        vector<ofxOscMessage> messages = p->getOSCMessages(message, useLegacy, cameraWidth, cameraHeight, bSendContours);
        for ( int i=0; i<messages.size(); i++){
            send(messages[i]);        
        }
    };
    
    void OscSender::personMoved ( Person * p, ofPoint centroid, int cameraWidth, int cameraHeight, bool bSendContours ){
        if(useLegacy){ //we just rely on person updated from now on
            string message = useLegacy ? "TSPS/personMoved/" : "/TSPS/personMoved/"; 
            vector<ofxOscMessage> messages = p->getOSCMessages(message, useLegacy, cameraWidth, cameraHeight, bSendContours);
            for ( int i=0; i<messages.size(); i++){
                send(messages[i]);        
            }
        }
    };
    
    void OscSender::personUpdated ( Person * p, ofPoint centroid, int cameraWidth, int cameraHeight, bool bSendContours ){
        string message = useLegacy ? "TSPS/personUpdated/" : "/TSPS/personUpdated/"; 
        vector<ofxOscMessage> messages = p->getOSCMessages(message, useLegacy, cameraWidth, cameraHeight, bSendContours);
        for ( int i=0; i<messages.size(); i++){
            send(messages[i]);        
        }
    };
    
    void OscSender::personWillLeave ( Person * p, ofPoint centroid, int cameraWidth, int cameraHeight, bool bSendContours ){
        string message = useLegacy ? "TSPS/personWillLeave/" : "/TSPS/personWillLeave/"; 
        vector<ofxOscMessage> messages = p->getOSCMessages(message, useLegacy, cameraWidth, cameraHeight, bSendContours);
        for ( int i=0; i<messages.size(); i++){
            send(messages[i]);        
        }	
    }
    
    void OscSender::send ( ofxOscMessage m ){
        sendMessage(m);
    };
    
    /***************************************************************
     REROUTE
     ***************************************************************/	
    
    void OscSender::reroute(string _ip, int _port){
        stringstream portstream;
        portstream<<_port;
        ofLog(OF_LOG_VERBOSE, "OscSender: REROUTING TO "+ip+", "+portstream.str());
        ip = _ip;
        port = _port;
        setup(ip, port);
    };
}