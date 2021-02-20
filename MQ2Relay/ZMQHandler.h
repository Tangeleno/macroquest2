#pragma once
//#define WINDOWS_IGNORE_PACKING_MISMATCH
#define ZMQ_STATIC
#include "zmq_addon.hpp"
#include <unordered_set>

enum class EQTopics:int
{
	None = 0,
	Join,
	Welcome,
	Announce,
	Depart,
	TargetUpdate,
	SelfUpdate,
	XTargetUpdate,
	TellReceived,
	Command,
	UpdateRequest,
	Acknowledged,
	BeginZone,
	EndZone,
	PetUpdate,
	GroupUpdate,
	AnnounceRequest,
	InventoryUpdate,
	StatUpdate,
	SpawnAdd,
	SpawnRemove,
	SpawnUpdate,
	FullSpawnUpdate,
	ZoneRequest
};

struct TopicPacket
{
	EQTopics Topic;
	std::vector<byte> Data;
};

class ZMQHandler
{
private:
	zmq::context_t* ctx_ = nullptr;
	zmq::socket_t* pubSocket_ = nullptr;
	zmq::socket_t* subSocket_ = nullptr;
	std::unordered_set<std::string> subbedTopics;
	std::vector<TopicPacket> topics_;
public:
	void Initialize(const std::string& publishAddress, const std::string& subscribeAddress);
	void Shutdown() const;
	void Send() const;
	void Send(EQTopics topic,const std::vector<byte>& id) const;
	void Send(EQTopics topic) const;
	void AppendTopic(EQTopics topic, const std::vector<unsigned char>& buffer, std::vector<byte>& id) const;
	void AppendTopic(EQTopics topic) const;
	bool Receive(std::vector<std::vector<byte>>& frames) const;
	void Unsubscribe(const std::string& topic);
	void Subscribe(const std::string& topic);
};

