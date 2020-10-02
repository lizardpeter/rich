
//created by lizardpeter
//testing 123
//1234

#include <iostream>
#include "discord.h"
#include <string>
#include <chrono>
#include <thread>

using namespace std;

discord::Core* core{};

string map1 = "Point of Contact";
string map2 = "Nightfall";
string map3 = "Mayday";
string map4 = "Awakening";
string map5 = "Exodus";

int hive = 0;
int update = 0;

auto result = discord::Core::Create(753812490525212762, DiscordCreateFlags_Default, &core);
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
		activity.SetDetails("Extinction on Point of Contact");
		activity.GetAssets().SetLargeImage("poc");
		activity.GetAssets().SetLargeText("Point of Contact");
		activity.GetAssets().SetSmallImage("ex");
		activity.GetAssets().SetSmallText("Extinction");
	}
	else if (map == map2)
	{
		activity.SetDetails("Extinction on Nightfall");
		activity.GetAssets().SetLargeImage("nf");
		activity.GetAssets().SetLargeText("Nightfall");
		activity.GetAssets().SetSmallImage("ex");
		activity.GetAssets().SetSmallText("Extinction");
	}
	else if (map == map3)
	{
		activity.SetDetails("Extinction on Mayday");
		activity.GetAssets().SetLargeImage("may");
		activity.GetAssets().SetLargeText("Mayday");
		activity.GetAssets().SetSmallImage("ex");
		activity.GetAssets().SetSmallText("Extinction");
	}
	else if (map == map4)
	{
		activity.SetDetails("Extinction on Awakening");
		activity.GetAssets().SetLargeImage("aw");
		activity.GetAssets().SetLargeText("Awakening");
		activity.GetAssets().SetSmallImage("ex");
		activity.GetAssets().SetSmallText("Extinction");
	}
	else
	{
		activity.SetDetails("Extinction on Exodus");
		activity.GetAssets().SetLargeImage("exo");
		activity.GetAssets().SetLargeText("Exodus");
		activity.GetAssets().SetSmallImage("ex");
		activity.GetAssets().SetSmallText("Extinction");
	}
	update++; //tell the thread Discord must be sent an update
	cout << "Map changed to " + map + "\n";
}

void changeMapThread()
{
	changeMap(map1);
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	changeMap(map2);
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	changeMap(map3);
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	changeMap(map4);
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	changeMap(map5);
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
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
	activity.SetState("Drilling Hive " + hive);
	activity.SetDetails("Extinction on Awakening");
	activity.GetAssets().SetLargeImage("aw");
	activity.GetAssets().SetLargeText("Awakening");
	activity.GetAssets().SetSmallImage("ex");
	activity.GetAssets().SetSmallText("Extinction");
	activity.GetTimestamps().SetStart(time(0));
	//activity.GetTimestamps().SetEnd(time(0) +5*60); //something like this if you want it to count backwards

	std::thread hives(timerz); //spawn the thread to change drill over time
	hives.detach();

	std::thread maps(changeMapThread); //spawn the thread to change the map over time
	maps.detach();

	std::thread update(updateDiscordThread); //spawn the thread to update Discord periodically
	update.detach();
	
	for (;;) //main program logic
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(15000));
	}
}
