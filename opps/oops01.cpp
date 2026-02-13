#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class Doceditor{
    private:
    vector<string>elements;
    string renderdoc;

    public:

    void addText(string text){
        elements.push_back(text);
    }
    void addImage(string img){
        elements.push_back(img);
    }

    string renderDocument(){
        if(elements.size()==0){
            cout<<"document is empty";
        }
        string result;

        for(auto ele:elements){
            if (ele.size() > 4 && (ele.substr(ele.size() - 4) == ".jpg" ||
                 ele.substr(ele.size() - 4) == ".png")){
                result+= "[image: "+ele+" ]"+ "\n";
            }else{
                result+=ele+"\n";
            }
        }
        renderdoc=result;
        return renderdoc;
    }

    void saveToFile(){

     ofstream file("document.txt");

     if(file.is_open()){
        file<<renderdoc;
        file.close();
        cout<<"doc has saved into the file"<<endl;
     }else{
       cout << "Error: Unable to open file for writing." << endl;
     }
    }
};

int main(){
    Doceditor editor;

    editor.addText("Hello, world!");
    editor.addImage("picture.jpg");
    editor.addText("This is a document editor.");

    cout << editor.renderDocument() << endl;

    editor.saveToFile();
    
    return 0;
}