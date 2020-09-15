
//created by lizardpeter

#include <iostream>
#include "discord.h"
#include <string>
#include <chrono>
#include <thread>

using namespace std; //branch test for bocw

discord::Core* core{};

string map1 = "Miami";
string map2 = "Satellite";
string map3 = "Armada";
string map4 = "Crossroads";
string map5 = "Moscow";

int hive = 0;
int update = 0;

auto result = discord::Core::Create(755272823647240282, DiscordCreateFlags_Default, &core);
discord::Activity activity{}; //replace the ID with your application ID

void updateDiscord() //this is called by updateDiscordThread
{
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
	cout << "Update sent\n";
}

void updateDiscordThread()
{
	do {
		//auto check = ::core->RunCallbacks();
		if (update == 1)
		{
			cout << "There is " + to_string(update) + " update queued\n";
			
		}
		else if (update > 1)
		{
			cout << "There are " + to_string(update) + " updates queued\n";
		}
		if (update > 0)
		{
			updateDiscord();
			update = 0;
		}
		//if (check == discord::Result::NotRunning) {
			//clearActivity();
		//}
		auto check = ::core->RunCallbacks();

		std::this_thread::sleep_for(std::chrono::milliseconds(16)); //polling rate
	} while (true);
}

void changeMap(string map) //this is called by changeMapThread
{
	if (map == map1)
	{
		activity.SetDetails("Playing Hardpoint on Miami");
		activity.GetAssets().SetLargeImage("cw");
		activity.GetAssets().SetLargeText("Miami");
		activity.GetAssets().SetSmallImage("smallz");
		activity.GetAssets().SetSmallText("Multiplayer");
	}
	else if (map == map2)
	{
		activity.SetDetails("Playing Hardpoint on Satellite");
		activity.GetAssets().SetLargeImage("cw");
		activity.GetAssets().SetLargeText("Satellite");
		activity.GetAssets().SetSmallImage("smallz");
		activity.GetAssets().SetSmallText("Multiplayer");
	}
	else if (map == map3)
	{
		activity.SetDetails("Hardpoint on Armada");
		activity.GetAssets().SetLargeImage("cw");
		activity.GetAssets().SetLargeText("Armada");
		activity.GetAssets().SetSmallImage("smallz");
		activity.GetAssets().SetSmallText("Multiplayer");
	}
	else if (map == map4)
	{
		activity.SetDetails("Playing Hardpoint on Crossroads");
		activity.GetAssets().SetLargeImage("cw");
		activity.GetAssets().SetLargeText("Crossroads");
		activity.GetAssets().SetSmallImage("smallz");
		activity.GetAssets().SetSmallText("Multiplayer");
	}
	else if (map == map5)
	{
		activity.SetDetails("Playing Hardpoint on Moscow");
		activity.GetAssets().SetLargeImage("cw");
		activity.GetAssets().SetLargeText("Moscow");
		activity.GetAssets().SetSmallImage("smallz");
		activity.GetAssets().SetSmallText("Multiplayer");
	}
	else
	{
		activity.SetDetails("In pre-game lobby");
		activity.GetAssets().SetLargeImage("cw");
		activity.GetAssets().SetLargeText("Call of Duty");
		activity.GetAssets().SetSmallImage("smallz");
		activity.GetAssets().SetSmallText("Cold War");
	}
	update++; //tell the thread Discord must be sent an update
	cout << "Map changed to " + map + "\n";
}

void changeMapThread()
{
	changeMap("stall");
	std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	changeMap(map1);
	std::this_thread::sleep_for(std::chrono::milliseconds(900000));
	changeMap("stall");
	std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	changeMap(map2);
	std::this_thread::sleep_for(std::chrono::milliseconds(900000));
	changeMap("stall");
	std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	changeMap(map3);
	std::this_thread::sleep_for(std::chrono::milliseconds(900000));
	changeMap("stall");
	std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	changeMap(map4);
	std::this_thread::sleep_for(std::chrono::milliseconds(900000));
	changeMap("stall");
	std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	changeMap(map5);
	std::this_thread::sleep_for(std::chrono::milliseconds(900000));
	changeMap("stall");
	std::this_thread::sleep_for(std::chrono::milliseconds(15000));
}

void timerz()
{
	int i = 0;
	//int last = 0;
	for (;;)
	{

		if (i < 100)
		{
			i++;
		}
		else if (i == 100)
		{
			i = 0;
		}
		else
		{
			i = 0;
		}
			
		hive = i;
		string str = "Drilling Hive " + to_string(hive) + "\n";
		const char* send = str.c_str();
		std::cout << send;
		activity.SetState(send);
		update++; //tell the thread Discord must be sent an update
		std::this_thread::sleep_for(std::chrono::milliseconds(15000)); //increase the drill count every 15 seconds

		//updateDiscord();
	}
}

int main() //basically nothing here matters and this program can just be made into a class
{
	//std::cout << "Hello World!\n";
	//discord::Core* core{};
	//discord::Core::Create(753812490525212762, DiscordCreateFlags_NoRequireDiscord, &core);
	//auto result = discord::Core::Create(753812490525212762, DiscordCreateFlags_Default, &core);
	//discord::Activity activity{};
	//activity.SetState("0");
	//activity.SetType(discord::ActivityType::Streaming);
	//here is the default/starting activity
	activity.SetDetails("In a party");
	//activity.SetDetails("Extinction on Awakening");
	activity.GetAssets().SetLargeImage("cw");
	activity.GetAssets().SetLargeText("Call of Duty");
	activity.GetAssets().SetSmallImage("smallz");
	activity.GetAssets().SetSmallText("Cold War");
	activity.GetTimestamps().SetStart(time(0));

	//activity.GetTimestamps().SetEnd(time(0) +5*60); //something like this if you want it to count backwards

	//std::thread hives(timerz); //spawn the thread to change drill over time
	//hives.detach();

	std::thread maps(changeMapThread); //spawn the thread to change the map over time
	maps.detach();

	std::thread update(updateDiscordThread); //spawn the thread to update Discord periodically
	update.detach();
	
	for (;;) //main program logic
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	}
}
