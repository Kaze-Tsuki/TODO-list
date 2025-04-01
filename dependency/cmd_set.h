#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept> // 用於拋出例外

using namespace std;

class CommandCustomizer {
private:
    vector<pair<string, vector<int>>>* commandList; // 儲存指令與對應的參數數量，保留順序
    string* name; // 儲存指令名稱
    int* numParams; // 儲存參數數量
    
public:
    // 建構函式，初始化指令名稱與參數數量，並從輸入中讀取指令定義
    CommandCustomizer(const string& attr) {
        commandList = new vector<pair<string, vector<int>>>(); // 保留原始指標
        name = new string();
        numParams = new int();

        auto ss = make_unique<stringstream>(attr);
        *ss >> *name; // 讀取指令名稱
        *ss >> *numParams; // 讀取參數數量
        cout << *name << ">>";
        auto s = make_unique<string>();
        while (getline(cin, *s)) {
            if (*s == "end")
                break;
            ss->clear(); // 清除錯誤狀態
            ss->str(*s); // 將字串設置為新的輸入流
            cout << *name << ">>";
            auto command = make_unique<string>();
            auto param = make_unique<string>();
            *ss >> *command; // 讀取指令名稱
            auto params = make_unique<vector<int>>();
            while (*ss >> *param) { // 讀取參數
                if (!isdigit((*param)[0]) || stoi(*param) < 1 || stoi(*param) > *numParams) // 檢查參數是否在範圍內
                    throw invalid_argument("Invalid parameter index: " + *param);
                else
                    params->push_back(stoi(*param));
            }
            commandList->emplace_back(*command, *params); // 儲存指令與參數，保留順序
        }
    }

    ~CommandCustomizer() {
        cout << "Deleting command " << *name << '\n';
        delete commandList;
        delete name;
        delete numParams;
    }

    // 獲取指令名稱
    string get_name() const {
        return *name;
    }

    // 獲取參數數量
    int get_numParams() const {
        return *numParams;
    }

    // 執行指令，根據參數生成結果
    string* execute(vector<string>& args) {
        if (args.size() != *numParams) {
            throw invalid_argument("Invalid number of parameters for command: " + *name +
                                   ". Expected: " + to_string(*numParams) +
                                   ", Provided: " + to_string(args.size()));
        }
        string* result = new string();
        *result = ""; // 清空結果字串
        for (auto& cmd : *commandList) {
            *result += cmd.first + " ";
            for (auto& param : cmd.second) {
                *result += args[param - 1] + " ";
            }
            *result += "\n";
        }
        return result;
    }
};
