/*
  ==============================================================================

    PlaylistComponent.h
    Created: 9 May 2022 2:54:25pm
    Author:  Steven

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeckGUI.h"
#include <fstream>

//==============================================================================
/*
*/
class PlaylistComponent : public Component,
    public TableListBoxModel,
    public Button::Listener


{
public:
    PlaylistComponent(DeckGUI* _deck1, DeckGUI* _deck2);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    enum {
        ID_TRACK_TITLE = 1,
        ID_LOAD,
        ID_LOAD_TO_A,
        ID_LOAD_TO_B
    };

    int getNumRows() override;
    void paintRowBackground(
        Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected
    ) override;
    void paintCell(
        Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected
    ) override;

    Component* refreshComponentForCell(
        int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate
    ) override;

    void buttonClicked(Button* button) override;

    void fileWrite(std::vector<juce::String> _trackTitle,
        std::vector<juce::URL> _URLVector);

    void fileRead();

private:
    TableListBox tableComponent;

    std::vector<juce::String> trackTitles;
    std::vector<juce::URL> URLVector;

    DeckGUI* deck1;
    DeckGUI* deck2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
