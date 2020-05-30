/*
  ==============================================================================

    MySender.cpp
    Created: 27 May 2020 3:42:22pm
    Author:  daveg

  ==============================================================================
*/

#include "MySender.h"

MySender::MySender()
{
    connect("127.0.0.1", 57120);
    type = tSection::matrix;
}

MySender::MySender(tSection type)
{
    this->type = type;
    connect("127.0.0.1", 57120);
}

MySender::~MySender()
{
}



void MySender::mySend(String name, float value) {

    String token1, token2, token3; // token1 module name, token 2 position and token3 additional position if matrix
    std::string delimiter = ">=", strTok3, stdName = name.toStdString(); //cast to std string


    token1 = String(stdName.substr(0, stdName.find(">=")).c_str()); //module name
    stdName.erase(0, stdName.find(delimiter) + delimiter.length()); //erase delimiter
    token2 = String(stdName.substr(0, stdName.find(">=")).c_str()); //position


    float token2float = std::stoi(token2.toStdString());  //cast position to float
    float token3float;


    stdName.erase(0, stdName.find(delimiter) + delimiter.length());

    if ((token1.toStdString().find(tSectionToString(tSection::matrix)) != std::string::npos) || 
        (token1.toStdString().find(tSectionToString(tSection::oscillator)) != std::string::npos) ||
        (token1.toStdString().find(tSectionToString(tSection::lfo)) != std::string::npos)) { //if matrix

        token3 = String(stdName.substr(0, stdName.find(">=")).c_str()); // additional position
        token3float = std::stoi(token3.toStdString());
        send(token1, int(token2float), int(token3float), value); //send
    }
    else {
        send(token1, int(token2float), value); //send
    }

}



String MySender::getSocketName()
{
    switch (type) {
        //case tSection::filter: return "/FmSynth/Filter";
    case tSection::matrix: return "/FmSynth/Matrix";          // receiving
    case tSection::lfo: return "/FmSynth/Lfo";                // receiving
    case tSection::oscillator: return "/FmSynth/Oscillator";  // receiving
    case tSection::master: return "/FmSynth/Master";          // receiving
    case tSection::envelope: return "/FmSynth/Envelope";
    default:
        break;
    }
    return "/StandardSocket"; //error case
}

tSection MySender::getTSection()
{
	return this->type;
}

std::string MySender::tSectionToString(tSection section)
{
    switch (section)
    {
    case tSection::filter: return "Filter";
    case tSection::matrix: return "Matrix";
    case tSection::oscillator: return "Oscillator";
    case tSection::lfo: return "Lfo";
    case tSection::master: return "Master";
    default: return "Matrix";
    }
    
}

tSection MySender::stringToTSection(String section)
{
    if (section == "Filter")
        return tSection::filter;
    if (section == "Matrix")
        return tSection::matrix;
    if (section == "Oscillator")
        return tSection::oscillator;
    if (section == "Lfo")
        return tSection::lfo;
    if (section == "Master")
        return tSection::master;

    return tSection::matrix;
}
