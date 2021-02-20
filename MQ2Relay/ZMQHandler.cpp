#include "ZMQHandler.h"

void ZMQHandler::Initialize(const std::string& publishAddress, const std::string& subscribeAddress)
{
	try
	{
		ctx_ = new zmq::context_t();
		pubSocket_ = new zmq::socket_t(*ctx_, zmq::socket_type::pub);
		subSocket_ = new zmq::socket_t(*ctx_, zmq::socket_type::sub);

		try
		{
			pubSocket_->connect(publishAddress);
		}
		catch (zmq::error_t error)
		{
			if (error.num() == 22)
			{
				//Can't Connect
			}
		}

		try
		{
			subSocket_->connect(subscribeAddress);
		}
		catch (zmq::error_t error)
		{
			if (error.num() == 22)
			{
				//Can't Connect
			}
		}
		
		
	}
	catch (zmq::error_t error)
	{
	}
	
}

void ZMQHandler::Shutdown() const
{
	auto linger = 0;
	subSocket_->setsockopt(ZMQ_LINGER, &linger, sizeof linger);
	pubSocket_->setsockopt(ZMQ_LINGER, &linger, sizeof linger);
	delete pubSocket_;
	delete subSocket_;
	delete ctx_;
}

void ZMQHandler::Send() const
{
	pubSocket_->send(nullptr, 0, 0);
}

void ZMQHandler::Send(EQTopics topic,const std::vector<unsigned char>& id) const
{
	pubSocket_->send(&topic, sizeof(int), ZMQ_SNDMORE);
	pubSocket_->send(&id[0], id.size(), 0);
}

void ZMQHandler::Send(EQTopics topic) const
{
	pubSocket_->send(&topic, sizeof(int), 0);
}

void ZMQHandler::AppendTopic(EQTopics topic, const std::vector<unsigned char>& buffer, std::vector<byte>& id) const
{
	if (id.empty())
		return;
	pubSocket_->send(&topic, sizeof(int), ZMQ_SNDMORE);
	pubSocket_->send(&id[0], id.size(), ZMQ_SNDMORE);
	if (buffer.empty())
		pubSocket_->send(nullptr, 0, ZMQ_SNDMORE);
	else
		pubSocket_->send(&buffer[0], buffer.size(), ZMQ_SNDMORE);
}

void ZMQHandler::AppendTopic(EQTopics topic) const
{
	pubSocket_->send(&topic, sizeof(int), ZMQ_SNDMORE);
	pubSocket_->send(nullptr, 0, ZMQ_SNDMORE);
}

bool ZMQHandler::Receive(std::vector<std::vector<byte>>& frames) const
{
	zmq::message_t msg;
	bool hasMessage = false;
	if(subSocket_->recv(&msg,ZMQ_NOBLOCK))
	{
		hasMessage = true;
		int more;
		auto more_size = sizeof more;
		subSocket_->getsockopt(ZMQ_RCVMORE, &more, &more_size);
		while (more)
		{
			subSocket_->recv(&msg);
			std::vector<byte> buffer;
			buffer.reserve(msg.size());
			for (size_t i = 0; i < msg.size(); ++i)
				buffer.push_back(static_cast<byte*>(msg.data())[i]);
			frames.push_back(buffer);
			subSocket_->getsockopt(ZMQ_RCVMORE, &more, &more_size);
		}
	}
	return hasMessage;
}

void ZMQHandler::Unsubscribe(const std::string& topic)
{
	subSocket_->setsockopt(ZMQ_UNSUBSCRIBE, topic.c_str(), topic.length());
}

void ZMQHandler::Subscribe(const std::string& topic)
{
	subSocket_->setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
}
