#include "DialogManager.h"

Story::Story()
{

    // Create StoryNode instances
    /*
    DialogNode node1;
    node1.id = 1;
    node1.type = "scene";
    node1.lines = { "You find yourself standing in a dimly lit alleyway.",
                   "The sound of footsteps echoes in the distance." };
    */

    DialogNode n1(0, 1, "scene", 
        { "one.",
         "two.",
        "three",
        "four",
        "five"
        });

    DialogNode n2(1, -1, "scene",
        { "A.",
          "B.",
        "C",
        "D"
        });

    DialogNode route1
        (2, -1, "scene",
        { "You made choice 1.",
          "you survived!."
        });

    DialogNode route2
    (3, -1, "scene",
        { "You made choice 2.",
          "you died."
        });



    /*
    DialogNode node2;
    node2.id = 2;
    node2.type = "scene";
    node2.lines = { "As you move closer, you see a shadowy figure emerge from the darkness.",
                   "It's a person wearing a hood, their face obscured." };
    */
    // Connect nodes with choices
    Choice choice1;
    choice1.text = "Investigate the source of the footsteps.";
    choice1.nextNode = route1.id;

    Choice choice2;
    choice2.text = "Investigate the source of the gays.";
    choice2.nextNode = route2.id;



    n2.choices.push_back(choice1);
    n2.choices.push_back(choice2);

    // Add nodes to the story
    nodes.push_back(n1);
    nodes.push_back(n2);

    nodes.push_back(route1);
    nodes.push_back(route2);

}

DialogNode::DialogNode(int pid, int pnextNodeID, std::string ptype, std::vector<std::string> plines)
{
    id = pid;
    type = ptype;
    nextNodeID = pnextNodeID;

    lines = plines;
    if (lines.size() > 0) {
        current = lines[0];
    }
    else current = "no lines in node";
}
