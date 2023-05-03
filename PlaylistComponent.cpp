/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 9 May 2022 2:54:25pm
    Author:  Steven

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deck1, DeckGUI* _deck2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    fileRead();
    addAndMakeVisible(tableComponent);

    trackTitles.resize(6);
    URLVector.resize(6);

    tableComponent.setModel(this);

    tableComponent.getHeader().addColumn("Track title", ID_TRACK_TITLE, 400);
    tableComponent.getHeader().addColumn("Play", ID_LOAD, 400);
    tableComponent.getHeader().addColumn("", ID_LOAD_TO_A, 200);
    tableComponent.getHeader().addColumn("", ID_LOAD_TO_B, 200);

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");

    deck1 = _deck1;
    deck2 = _deck2;
}

PlaylistComponent::~PlaylistComponent()
{
    fileWrite(trackTitles, URLVector);

}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(
    Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected
) {
    // just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}
void PlaylistComponent::paintCell(
    Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected
) {
    g.drawText(
        trackTitles[rowNumber], // the important bit
        2, 0,
        width - 4, height,
        Justification::centredLeft,
        true
    );
}

Component* PlaylistComponent::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate
) {
    if (ID_LOAD == columnId)
    {
        if (!existingComponentToUpdate)
        {

            auto* btn = new TextButton("Load");
            btn->setComponentID(std::to_string(rowNumber));
            existingComponentToUpdate = btn;
            btn->addListener(this);
        }
    }
    if (ID_LOAD_TO_A == columnId)
    {
        if (!existingComponentToUpdate)
        {
            auto* btn = new TextButton("Load to A");
            btn->setComponentID(std::to_string(rowNumber));
            existingComponentToUpdate = btn;
            btn->addListener(this);
        }
    }
    if (ID_LOAD_TO_B == columnId)
    {
        if (!existingComponentToUpdate)
        {
            auto* btn = new TextButton("Load to B");
            btn->setComponentID(std::to_string(rowNumber));
            existingComponentToUpdate = btn;
            btn->addListener(this);
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());

    if (button->getButtonText() == "Load to A")
    {
        int id = std::stoi(button->getComponentID().toStdString());
        deck1->loadURL(URLVector[id]);
    }
    if (button->getButtonText() == "Load to B")
    {
        int id = std::stoi(button->getComponentID().toStdString());
        deck2->loadURL(URLVector[id]);
    }
    if (button->getButtonText() == "Load")
    {
        int id = std::stoi(button->getComponentID().toStdString());
        FileChooser chooser{ "Select a file..." };
        if (chooser.browseForFileToOpen())
        {
            URLVector[id] = URL{chooser.getResult()};
            trackTitles[id] = URLVector[id].getFileName(); repaint();
        }
    }
        
}

void PlaylistComponent::fileWrite(std::vector<juce::String> _trackTitle, std::vector<juce::URL> _URLVector)
{
    std::ofstream fileWriteTitle("titleSaveState.txt");
    std::ofstream fileWriteURL("urlSaveState.txt");
    for (juce::String i : _trackTitle) { fileWriteTitle << i << std::endl;  }
    for (juce::URL i : _URLVector) { fileWriteURL << i.toString(true) << std::endl; }

    fileWriteTitle.close();
    fileWriteURL.close();

}

void PlaylistComponent::fileRead()
{
    std::ifstream fileReadTitle("titleSaveState.txt");
    std::ifstream fileReadURL("urlSaveState.txt");
    std::string tempString;
    juce::String tempStringJuce;
    if (fileReadTitle.is_open())
    {
        while (std::getline(fileReadTitle, tempString)) { trackTitles.push_back(tempString); }
    }
    if (fileReadURL.is_open())
    {
        while (std::getline(fileReadURL, tempString))
        {
            tempStringJuce = tempString;
            URLVector.push_back(tempStringJuce);
        }
    }
}



