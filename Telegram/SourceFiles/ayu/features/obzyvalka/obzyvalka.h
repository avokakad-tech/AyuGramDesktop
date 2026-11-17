// AyuGram Desktop - Obzyvalka local AI message transformer.
#pragma once

#include "data/data_msg_id.h"
#include "rpl/lifetime.h"

#include <optional>

#include <QObject>
#include <QNetworkAccessManager>

#include <map>
#include <set>

namespace Main {
class Session;
}

class HistoryItem;

namespace Ayu {

class Obzyvalka final : public QObject {
public:
	explicit Obzyvalka(not_null<Main::Session*> session);
	~Obzyvalka() override = default;

	[[nodiscard]] std::optional<QString> displayText(FullMsgId id) const;

private:
	void handleNewItem(not_null<HistoryItem*> item);
	void requestRewrite(not_null<HistoryItem*> item, const QString &text);

	const not_null<Main::Session*> _session;
	QNetworkAccessManager _network;
	std::set<FullMsgId> _processed;
	std::map<FullMsgId, not_null<HistoryItem*>> _pendingItems;
	struct DisplayOverride {
		QString text;
		uint64 senderId = 0;
	};
	std::map<FullMsgId, DisplayOverride> _displayText;
	qint64 _lastAutomaticReplyMs = 0;
	rpl::lifetime _lifetime;
};

} // namespace Ayu
