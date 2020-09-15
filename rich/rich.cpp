
//created by lizardpeter

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

void updateDiscord()
{
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
	cout << "update sent";
}

void updateDiscordThread()
{
	do {
		//auto check = ::core->RunCallbacks();
		cout << update;
		if (update > 0)
		{
			updateDiscord();
			update = 0;
		}
		//if (check == discord::Result::NotRunning) {
			//clearActivity();
		//}
		auto check = ::core->RunCallbacks();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	} while (true);
}




void changeMap(string map)
{
	if (map == map1)
	{
		activity.SetDetails("Extinction on Point of Contact");
		activity.GetAssets().SetLargeImage("poc");
		activity.GetAssets().SetLargeText("Point of Contact");
		activity.GetAssets().SetSmallImage("ex");
		activity.GetAssets().SetSmallText("Extinction");
		//activity.SetType(discord::ActivityType::Watching);
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
	update++;
	std::this_thread::sleep_for(std::chrono::milliseconds(100000)); //change the map every 100 seconds
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
		string str = "Drilling Hive " + to_string(hive);
		const char* send = str.c_str();
		std::cout << send;
		activity.SetState(send);
		update++;
		std::this_thread::sleep_for(std::chrono::milliseconds(15000)); //increase the drill count every 15 seconds

		//updateDiscord();
	}
}

int main()
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
	//activity.GetTimestamps().SetEnd(time(0) +5*60); //something like this if you want it to cound backwards

	std::thread hives(timerz); //spawn the thread to change drill over time
	hives.detach();

	std::thread update(updateDiscordThread); //spawn the thread to update discord periodically
	update.detach();

	

	//activity.GetParty().SetId("ae488379-351d-4a4f-ad32-2b9b01c91657");
	//activity.SetInstance("ae488379-351d-4a4f-ad32-2b9b01c91657");
	//activity.GetAssets.


	//core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		//});
	
	for (;;)
	{
		//::core->RunCallbacks();
		//int i = 12;
		changeMap(map1);
		//updateDiscord();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		changeMap(map2);
		//updateDiscord();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		changeMap(map3);
		//updateDiscord();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		changeMap(map4);
		//updateDiscord();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		changeMap(map5);
		//updateDiscord();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		//activity.SetState("test");
		//core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

			
			
		
			//});
	}
}
