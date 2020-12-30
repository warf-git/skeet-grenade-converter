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

int main() {
    string map, file;
    cout << "Enter file name(ex: grenades.json)" << endl;
    cin >> file;
    cout << "Enter map name(ex: de_vertigo)" << endl;
    cin >> map;
    Json::Value v2data;
    Json::Value nulljs;

    std::ifstream helper_file(file, std::ifstream::binary); //read from v2data.json
    helper_file >> v2data;

    Json::Value host;

    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value(2));

    int cnt = 0;
    int nonullcnt = 0;
    for (auto i = v2data.begin(); i != v2data.end(); ++i) {
        if (v2data[cnt]["map"] != map) {
            cnt++;
            continue;
        }
        Json::Value v2dataparsed[] = { v2data[cnt]["from"], v2data[cnt]["to"], v2data[cnt]["weapon"], v2data[cnt]["x"], v2data[cnt]["y"], v2data[cnt]["z"], v2data[cnt]["duck"], v2data[cnt]["throwStrength"], v2data[cnt]["throwType"], v2data[cnt]["runDuration"], v2data[cnt]["pitch"] , v2data[cnt]["yaw"] };
        Json::Value name_host;
        name_host.append(v2dataparsed[0]);
        name_host.append(v2dataparsed[1]);
        host[map][nonullcnt]["name"] = name_host;
        host[map][nonullcnt]["weapon"] = v2dataparsed[2];
        Json::Value position_host;
        position_host.append(v2dataparsed[3]);
        position_host.append(v2dataparsed[4]);
        position_host.append(v2dataparsed[5]);
        host[map][nonullcnt]["position"] = position_host;
        Json::Value view_host;
        view_host.append(v2dataparsed[10]);
        view_host.append(v2dataparsed[11]);
        host[map][nonullcnt]["viewangles"] = view_host;
        if (v2dataparsed[6] != nulljs) host[map][nonullcnt]["duck"] = v2dataparsed[6];
        if (v2dataparsed[7] != nulljs) host[map][nonullcnt]["grenade"]["strength"] = v2dataparsed[7];
        if (v2dataparsed[8] == "RUNJUMP" || v2dataparsed[8] == "JUMP") host[map][nonullcnt]["grenade"]["jump"] = true;
        if (v2dataparsed[9] != nulljs && v2dataparsed[9] != 0) host[map][nonullcnt]["grenade"]["run"] = v2dataparsed[9];
        else if (v2dataparsed[8] == "RUNJUMP" || v2dataparsed[8] == "RUN") host[map][nonullcnt]["grenade"]["run"] = 20;
        cnt++;
        nonullcnt++;
    }

    int entry = cnt;

    cout << host << std::endl;
    ofstream file_id;

    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::ofstream outputFileStream("nades.json");
    writer->write(host, &outputFileStream);

    file_id.close();
}