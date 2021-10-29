//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {

    string line;
    string command;
    bool maxShapesCalled = false; 
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        bool readyForNew = false; // check if we're done with processing this command 
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        if (lineStream.peek() == -1) {
            ////////////////////////error 0////////////////////////////
                        cout << "Error: invalid command" << endl; 
                        readyForNew = true; 
        } // make sure there's nothing after arguments 
        lineStream >> command;

        
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        while (readyForNew==false) {
            bool match = false; // check if match the keyWordList 
            for (int i=0; i<7 && match==false; i++) {
                if (keyWordsList[i]==command) {
                    match = true; // the command is valid because the keyWord matches 
                }
            }
            if (match==false) { // the command is invalid 
                ////////////////////////error 0.5////////////////////////////
                cout << "Error: invalid command" << endl; 
                readyForNew = true; 
                // break; 
            }
            
            if (command=="maxShapes") { // command is maxShapes 
                if (maxShapesCalled==true) {
                    for (int i=0; i<max_shapes; i++) {
                        if (shapesArray[i]!=NULL) {
                        delete shapesArray[i]; 
                        shapesArray[i] = NULL; 
                        }
                    }
                    delete [] shapesArray; 
                    shapeCount = 0; 
                } 
                lineStream >> max_shapes; 
                shapesArray = new Shape*[max_shapes]; 
                for (int i=0; i<max_shapes; i++) {
                    shapesArray[i] = NULL; 
                }
                //cout << "Max Shape is: " << max_shapes << endl; 
                cout << "New database: max shapes is " << max_shapes << endl; 
                readyForNew = true;
                maxShapesCalled = true; 
            } else if (command=="create") { // command is create 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 1////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after create   
                string name; 
                //cout << "Peek: " << lineStream.peek() << endl; 
                lineStream >> name; 
                //cout << "Peek: " << lineStream.peek() << endl; 
                //cout << "name is:" << name << endl; 
                bool isNameInvalid = false; 
                for (int i=0; i<7 && isNameInvalid==false; i++) {
                    if (keyWordsList[i]==name) {
                        isNameInvalid = true; 
                    }
                } 
                if (isNameInvalid==true) {
                ////////////////////////error 2////////////////////////////
                        cout << "Error: invalid shape name" << endl; 
                        readyForNew = true; 
                        break; 
                }
                bool nameInvalid = false; 
                for (int i=0; i<4&&nameInvalid==false; i++) {
                    if (shapeTypesList[i]==name) {
                        nameInvalid = true; 
                    }
                } 
                if (nameInvalid==true) { //// now we're sure the name is valid
                    ////////////////////////error 3////////////////////////////
                    cout << "Error: invalid shape name" << endl; 
                    readyForNew = true;
                    break; 
                }
                bool nameCreated = false; 
                int i; 
                for (i=0; i<max_shapes && nameCreated==false; i++) {
                    if (shapesArray[i]!=NULL&&name==(*shapesArray[i]).getName()) { 
                        nameCreated = true; 
                    }
                } /// see if name has been created before 
                if (nameCreated==true) {
                    ////////////////////////error 3.5////////////////////////////
                    cout << "Error: shape " << (*shapesArray[i-1]).getName() 
                            <<  " exists" << endl; 
                    readyForNew = true;
                    break; 
                }
                if (lineStream.peek() == -1) {
                    ////////////////////////error 4////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after name  

                string type; 
                lineStream >> type; 
                //cout << "type is: " << type << endl; 
                bool goodType = false; 
                for (int i=0; i<4 && goodType==false; i++) {
                    if (shapeTypesList[i]==type) {
                        goodType = true; 
                    }
                }
                if (goodType==false) { // the type entered is invalid 
                    ////////////////////////error 5////////////////////////////
                    cout << "Error: invalid shape type" << endl; 
                    readyForNew = true; 
                    break; 
                } //// now we're sure the type is valid 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 6////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after type 
                int x_loc, y_loc, x_sz, y_sz; 
                lineStream >> x_loc; 
                //cout << "x_loc: " << x_loc << endl; 
                if (lineStream.fail()) {
                    ////////////////////////error 7////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (x_loc<0) {
                    ////////////////////////error 8////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure x_loc is valid 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 9////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after x_loc  
                lineStream >> y_loc; 
                //cout << "y_loc: " << y_loc << endl; 
                if (lineStream.fail()) {
                    ////////////////////////error 10////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (y_loc<0) {
                    ////////////////////////error 11////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure y_loc is valid 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 12////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after y_loc 
                lineStream >> x_sz;
                //cout << "x_sz: " << x_sz << endl; 
                if (lineStream.fail()) {
                    ////////////////////////error 13////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (x_sz<0) {
                    ////////////////////////error 14////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure x_sz is valid 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 15////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after x_sz 
                lineStream >> y_sz; 
                //cout << "y_sz: " << y_sz << endl; 
                if (lineStream.fail()) {
                    ////////////////////////error 16////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (y_sz<0) {
                    ////////////////////////error 17////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure y_loc is valid  
                if (type == "circle") {
                    if (x_sz!=y_sz) {
                        ////////////////////////error 18////////////////////////////
                        cout << "Error: invalid value" << endl; 
                        readyForNew = true; 
                        break; 
                    }
                } // The loc and sz are valid 
                if (lineStream.peek() != -1) {
                    ////////////////////////error 19////////////////////////////
                    cout << "Error: too many arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's nothing after y_sz 
                if (shapeCount==max_shapes) {
                    ////////////////////////error 19.5////////////////////////////
                    cout << "Error: shape array is full" << endl; 
                    readyForNew = true; 
                    break; 
                } // to make sure there is more space to create new shape 
                cout << "Created " << name << ": " << type << " " << x_loc << " " 
                        << y_loc << " " << x_sz << " " << y_sz << endl; 
                ////// almost there! 
                shapesArray[shapeCount] = new Shape(name, type, x_loc, x_sz, y_loc, y_sz); 
                //(*shapesArray[shapeCount]).draw(); 
                //cout << "this is *shapesArray[" << shapeCount << "]" << endl; 
                shapeCount++; 
                //cout << "shapeCount is now: " << shapeCount << endl; 
                /// new "box" (pointer to Shape) initialized in shapesArray 
                readyForNew = true; 
                break; 
                /// everything is good 
            } else if (command=="move") { // command is move 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 20////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after move 
                string name; 
                lineStream >> name; 
                bool nameCreated = false; 
                int i; 
                for (i=0; i<max_shapes && nameCreated==false; i++) {
                    if (shapesArray[i]!=NULL&&name==(*shapesArray[i]).getName()) { 
                        nameCreated = true; 
                        //cout << "i in loop is: " << i << endl; 
                    }
                } /// see if name has been created before 
                //cout << "i is: " << i << endl; 
                if (nameCreated==false) {
                    ////////////////////////error 21////////////////////////////
                    cout << "Error: shape " << name << " not found" << endl; 
                    readyForNew = true;
                    break; 
                } /// now the name is valid and good for use 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 22////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after name  
                int x_loc, y_loc; 
                lineStream >> x_loc; 
                //cout << "x_loc: " << x_loc << endl; 
                if (lineStream.fail()) {
                    ////////////////////////error 23////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (x_loc<0) {
                    ////////////////////////error 24////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure x_loc is valid 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 25////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after x_loc  
                lineStream >> y_loc; 
                //cout << "y_loc: " << y_loc << endl; 
                if (lineStream.fail()) {
                    ////////////////////////error 26////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (y_loc<0) {
                    ////////////////////////error 27////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure y_loc is valid 
                if (lineStream.peek() != -1) {
                    ////////////////////////error 28////////////////////////////
                    cout << "Error: too many arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's nothing after y_loc 
                /// almost there 
                cout << "Moved " << name << " to " << x_loc << " " << y_loc << endl; 
                (*shapesArray[i-1]).setXlocation(x_loc); 
                (*shapesArray[i-1]).setYlocation(y_loc); 
                //(*shapesArray[i-1]).draw(); 
                readyForNew = true; 
                break; 
                
            } else if (command=="rotate") { // command is rotate 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 29////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after rotate  
                string name; 
                lineStream >> name; 
                bool nameCreated = false; 
                int i; 
                for (i=0; i<max_shapes && nameCreated==false; i++) {
                    if (shapesArray[i]!=NULL&&name==(*shapesArray[i]).getName()) { 
                        nameCreated = true; 
                        //cout << "i in loop is: " << i << endl; 
                    }
                } /// see if name has been created before 
                //cout << "i is: " << i << endl; 
                if (nameCreated==false) {
                    ////////////////////////error 30////////////////////////////
                    cout << "Error: shape " << name << " not found" << endl; 
                    readyForNew = true;
                    break; 
                } /// now the name is valid and good for use 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 31////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after name  
                int angle; 
                lineStream >> angle; 
                //cout << "angle: " << angle << endl; 
                if (lineStream.fail()) { 
                    ////////////////////////error 32////////////////////////////
                    cout << "Error: invalid argument" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                if (angle<0 || angle>360) {
                    ////////////////////////error 33////////////////////////////
                    cout << "Error: invalid value" << endl; 
                    readyForNew = true; 
                    break; 
                } // now we're sure angle is valid 
                if (lineStream.peek() != -1) {
                    ////////////////////////error 34////////////////////////////
                    cout << "Error: too many arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's nothing after angle 
                /// almost there! 
                cout << "Rotated " << name << " by " << angle << " degrees" << endl; 
                (*shapesArray[i-1]).setRotate(angle); 
                //(*shapesArray[i-1]).draw(); 
                readyForNew = true; 
                break; 
            } else if (command=="draw") { // command is draw 
                string arguments; 
                //cout << "peek is: " << lineStream.peek() << endl; 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 35////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after draw 
                lineStream >> arguments; 
                if (arguments=="all") { /// draw all 
                    if (lineStream.peek() != -1) {
                        ////////////////////////error 36////////////////////////////
                        cout << "Error: too many arguments" << endl; 
                        readyForNew = true; 
                        break; 
                    } // make sure there's nothing after all 
                    cout << "Drew all shapes" << endl; 
                    for (int i=0; i<max_shapes; i++) {
                        if (shapesArray[i]!=NULL) {
                            //cout << "draw below shapesArray[" << i << "]" << endl; 
                            (*shapesArray[i]).draw();
                        } 
                    }
                    readyForNew = true; 
                    break; 
                } 
                bool nameCreated = false; 
                int i; 
                for (i=0; i<max_shapes && nameCreated==false; i++) {
                    if (shapesArray[i]!=NULL&&arguments==(*shapesArray[i]).getName()) { 
                        nameCreated = true; 
                        //cout << "i in loop is: " << i << endl; 
                    }
                } /// see if name has been created before 
                //cout << "i is: " << i << endl; 
                if (nameCreated==false) {
                    ////////////////////////error 37////////////////////////////
                    cout << "Error: shape " << arguments << " not found" << endl; 
                    readyForNew = true;
                    break; 
                } /// now the name is valid and good for use 
                if (lineStream.peek() != -1) {
                    ////////////////////////error 38////////////////////////////
                        cout << "Error: too many arguments" << endl; 
                        readyForNew = true; 
                        break; 
                } // make sure there's nothing after arguments 
                //cout << "Drew " << ((*shapesArray[i-1]).draw()) << endl;
                cout << "Drew "; 
                (*shapesArray[i-1]).draw(); 
                //cout << endl; 
                readyForNew = true; 
                break; 
            } else if (command=="delete") { // command is delete 
                string arguments; 
                //cout << "peek is: " << lineStream.peek() << endl; 
                if (lineStream.peek() == -1) {
                    ////////////////////////error 39////////////////////////////
                    cout << "Error: too few arguments" << endl; 
                    readyForNew = true; 
                    break; 
                } // we're sure there's something else after draw 
                lineStream >> arguments; 
                if (arguments=="all") { /// delete all 
                    if (lineStream.peek() != -1) {
                        ////////////////////////error 40////////////////////////////
                        cout << "Error: too many arguments" << endl; 
                        readyForNew = true; 
                        break; 
                    } // make sure there's nothing after all 
                    for (int i=0; i<max_shapes; i++) {
                        if (shapesArray[i]!=NULL) { 
                        delete shapesArray[i]; 
                        shapesArray[i] = NULL; 
                        //cout << "deleted shapesArray[" << i << "]" << endl; 
                        } 
                    } 
                    cout << "Deleted: all shapes" << endl; 
                    readyForNew = true; 
                    break; 
                } 
                bool nameCreated = false; 
                int i; 
                for (i=0; i<max_shapes && nameCreated==false; i++) {
                    if (shapesArray[i]!=NULL&&arguments==(*shapesArray[i]).getName()) { 
                        nameCreated = true; 
                        //cout << "i in loop is: " << i << endl; 
                    }
                } /// see if name has been created before 
                //cout << "i is: " << i << endl; 
                if (nameCreated==false) {
                    ////////////////////////error 41////////////////////////////
                    cout << "Error: shape " << arguments << " not found" << endl; 
                    readyForNew = true;
                    break; 
                } /// now the name is valid and good for use 
                if (lineStream.peek() != -1) {
                    ////////////////////////error 42////////////////////////////
                        cout << "Error: too many arguments" << endl; 
                        readyForNew = true; 
                        break; 
                } // make sure there's nothing after arguments 
                cout << "Deleted shape " << (*shapesArray[i-1]).getName() << endl; 
                //cout << "deleted shapesArray["<< i-1 << "]" << endl; 
                delete shapesArray[i-1]; 
                shapesArray[i-1] = NULL; 
                readyForNew = true; 
                break; 
            }
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

