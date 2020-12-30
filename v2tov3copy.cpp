#include "json/json.h"
#include "json/json-forwards.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
#include <string>
#include <sstream>

using namespace std;

const char* json_types[18] = { "from", "landX", "landY", "landZ", "map", "pitch", "runDuration", "throwType", "to", "type", "viewAnglesDistanceMax", "weapon", "x", "y", "yaw", "z", "throwStrength", "duck" };
const char* v3_types[] = { "name", "description", "weapon", "position", "position_visibility", "viewangles", "duck", "tickrate", "approach_accurate", "strength", "fov", "jump", "run", "run_yaw", "run_speed", "recovery_yaw", "delay", "start", "end", "text", "target" };

int printMissingIndexes(Json::Value v2data)
{
    int cnt = 0;
    for (auto i = v2data.begin(); i != v2data.end(); ++i) {

        for (auto const& id : v2data[cnt].getMemberNames()) {
            bool in_array = false;
            for (int i = 0; i < *(&json_types + 1) - json_types; i++) {
                if (id == json_types[i]) {
                    in_array = true;
                }
            }
            if (in_array == false) cout << id << endl;

        }

        cnt++;
    }

    return 0;

}

void enter_v3data(Json::Value host, int entry, Json::Value parseArray) {   // v2data[0]["map2"] -> returns null

    /*Json::Value name_host;
    name_host.append(parseArray[0]);
    name_host.append(parseArray[1]);
    host[entry]["name"] = name_host;
    host[entry]["weapon"] = parseArray[2];
    Json::Value position_host;
    position_host.append(parseArray[3]);
    position_host.append(parseArray[4]);
    position_host.append(parseArray[5]);
    host[entry]["position"] = position_host;
    if(parseArray[6] != NULL) host[entry]["duck"] = parseArray[6];
    if(parseArray[7] != "null") host[entry]["grenade"]["strength"] = parseArray[7];
    if(parseArray[8] != "NORMAL") host[entry]["grenade"]["jump"] = parseArray[8];
    if(parseArray[9] != "null") host[entry]["grenade"]["run"] = parseArray[9];
    if(parseArray[9] == "0") host[entry]["grenade"]["run"] = 1;*/
}

int main() {
    Json::Value v2data;
    Json::Value nulljs;

    std::ifstream helper_file("v2data.json", std::ifstream::binary); //read from v2data.json
    helper_file >> v2data;

    Json::Value host;

    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value(2));

    int cnt = 0;
    int nonullcnt = 0;
    for (auto i = v2data.begin(); i != v2data.end(); ++i) {
        if (v2data[cnt]["map"] != "de_lake") {
            cnt++;
            continue;
        }
        Json::Value v2dataparsed[] = { v2data[cnt]["from"], v2data[cnt]["to"], v2data[cnt]["weapon"], v2data[cnt]["x"], v2data[cnt]["y"], v2data[cnt]["z"], v2data[cnt]["duck"], v2data[cnt]["throwStrength"], v2data[cnt]["throwType"], v2data[cnt]["runDuration"], v2data[cnt]["pitch"] , v2data[cnt]["yaw"] };
        Json::Value name_host;
        name_host.append(v2dataparsed[0]);
        name_host.append(v2dataparsed[1]);
        host[nonullcnt]["name"] = name_host;
        host[nonullcnt]["weapon"] = v2dataparsed[2];
        Json::Value position_host;
        position_host.append(v2dataparsed[3]);
        position_host.append(v2dataparsed[4]);
        position_host.append(v2dataparsed[5]);
        host[nonullcnt]["position"] = position_host;
        Json::Value view_host;
        view_host.append(v2dataparsed[10]);
        view_host.append(v2dataparsed[11]);
        host[nonullcnt]["viewangles"] = view_host;
        if (v2dataparsed[6] != nulljs) host[nonullcnt]["duck"] = v2dataparsed[6];
        if (v2dataparsed[7] != nulljs) host[nonullcnt]["grenade"]["strength"] = v2dataparsed[7];
        if (v2dataparsed[8] == "RUNJUMP" || v2dataparsed[8] == "JUMP") host[nonullcnt]["grenade"]["jump"] = true;
        if (v2dataparsed[9] != nulljs && v2dataparsed[9] != 0) host[nonullcnt]["grenade"]["run"] = v2dataparsed[9];
        else if (v2dataparsed[9] == 0) host[nonullcnt]["grenade"]["run"] = 1;
        else if (v2dataparsed[8] == "RUNJUMP" || v2dataparsed[8] == "RUN") host[nonullcnt]["grenade"]["run"] = 20;
        cnt++;
        nonullcnt++;

    }

    int entry = cnt;


    cout << host << std::endl;
}