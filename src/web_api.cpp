#include "web_api.h"
#include "emscripten/emscripten.h"
#include "output.h"

using namespace Web_API;

void Web_API::OnLoadMap(std::string_view name) {
	EM_ASM({
		onLoadMap(UTF8ToString($0));
	}, name.data(), name.size());
}

std::string Web_API::GetSocketURL() {
	return reinterpret_cast<char*>(EM_ASM_INT({
	  var ws = Module.EASYRPG_WS_URL;
	  var len = lengthBytesUTF8(ws)+1;
	  var wasm_str = _malloc(len);
	  stringToUTF8(ws, wasm_str, len);
	  return wasm_str;
	}));
}

void Web_API::OnUpdatePlayerCount(std::string_view countstr) {
	EM_ASM({
		updatePlayerCount(UTF8ToString($0, $1));
	}, countstr.data(), countstr.size());
}

void Web_API::OnChatMessageReceived(std::string_view sys, std::string_view msg) {
	EM_ASM({
		onChatMessageReceived(UTF8ToString($0, $1), UTF8ToString($2, $3));
	}, sys.data(), sys.size(), msg.data(), msg.size());
}

void Web_API::OnPlayerDisconnect(int id) {
	EM_ASM({
		onPlayerDisconnected($0);
	}, id);
}

void Web_API::OnPlayerUpdated(std::string_view name, int id) {
	EM_ASM({
		onPlayerConnectedOrUpdated(UTF8ToString($0, $1), "", $2);
	}, name.data(), name.size(), id);
}

void Web_API::UpdateConnectionStatus(int status) {
	EM_ASM({
		onUpdateConnectionStatus($0);
	}, status);
}

void Web_API::ReceiveInputFeedback(int s) {
	EM_ASM({
		onReceiveInputFeedback($0);
	}, s);
}

void Web_API::OnPlayerSpriteUpdated(std::string_view name, int index, int id) {
	EM_ASM({
		onPlayerSpriteUpdated(UTF8ToString($0, $1), $2, $3);
	}, name.data(), name.size(), index, id);
}

void Web_API::OnUpdateSystemGraphic(std::string_view sys) {
	EM_ASM({
		onUpdateSystemGraphic(UTF8ToString($0, $1));
	}, sys.data(), sys.size());
}

