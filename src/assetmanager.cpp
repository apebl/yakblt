#include "assetmanager.hpp"

namespace yakblt {
	/* class StreamResolver */

	StreamResolver::~StreamResolver () {
	}

	/* class DefaultResolver */

	InputStream *DefaultResolver::resolve (const string &path) {
		FileInputStream *stream = new FileInputStream();
		stream->open("assets/" + path);
		return stream;
	};

	AssetManager::TextureOptions::TextureOptions (bool smooth, bool mipmap, const IntRect &area) :
			smooth(smooth), mipmap(mipmap), area(area)
	{
	}

	/* class AssetManager */

	AssetManager::AssetManager (StreamResolver &resolver) {
		_resolver = &resolver;
	}

	AssetManager::~AssetManager () {
		delete _resolver;
		for (auto pair : _textures) {
			delete pair.second;
		}
		for (auto pair : _soundBuffers) {
			delete pair.second;
		}
		for (auto pair : _fonts) {
			delete pair.second;
		}
	}

	StreamResolver &AssetManager::getResolver () const {
		return *_resolver;
	}

	const Texture &AssetManager::loadTexture (const string &path, const TextureOptions &opt) {
		auto iter = _textures.find(path);
		if (iter != _textures.end()) {
			return *iter->second;
		} else {
			InputStream *stream = _resolver->resolve(path);
			Texture *tex = new Texture();
			bool result = tex->loadFromStream(*stream, opt.area);
			delete stream;
			if (!result) throw runtime_error("Failed to load texture file: " + path);
			_textures.emplace(path, tex);
			tex->setSmooth(opt.smooth);
			if (opt.mipmap) tex->generateMipmap();
			return *tex;
		}
	}

	const SoundBuffer &AssetManager::loadSoundBuffer (const string &path) {
		auto iter = _soundBuffers.find(path);
		if (iter != _soundBuffers.end()) {
			return *iter->second;
		} else {
			InputStream *stream = _resolver->resolve(path);
			SoundBuffer *buf = new SoundBuffer();
			bool result = buf->loadFromStream(*stream);
			delete stream;
			if (!result) throw runtime_error("Failed to load sound buffer file: " + path);
			_soundBuffers.emplace(path, buf);
			return *buf;
		}
	}

	const Font &AssetManager::loadFont (const string &path) {
		auto iter = _fonts.find(path);
		if (iter != _fonts.end()) {
			return *iter->second->font;
		} else {
			InputStream *stream = _resolver->resolve(path);
			Font *font = new Font();
			bool result = font->loadFromStream(*stream);
			// Do not delete the stream.
			// It has to remain accessible until the sf::Font object loads
			// a new font or is destroyed.
			if (!result) throw runtime_error("Failed to load font file: " + path);
			_fonts.emplace( path, new FontAsset(*font, *stream) );
			return *font;
		}
	}

	AssetManager::FontAsset::FontAsset (const Font &font, const InputStream &stream) :
			font(&font), stream(&stream)
	{
	}

	AssetManager::FontAsset::~FontAsset () {
		delete font;
		delete stream;
	}
}
