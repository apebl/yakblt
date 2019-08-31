#ifndef __BLT_ASSETMANAGER_H__
#define __BLT_ASSETMANAGER_H__

#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

namespace blt {
	class StreamResolver {
	public:
		virtual ~StreamResolver ();
		/**
		 * Maps the given path to a input stream and returns the stream.
		 *
		 * @note You have to delete the returned stream yourself.
		 *
		 * @return The result stream
		 */
		virtual InputStream *resolve (const string &path) = 0;
	};

	class DefaultResolver : public StreamResolver {
	public:
		virtual InputStream *resolve (const string &path) override;
	};

	/*
	 * @note AssetManagers hold the ownership of the assets and the resolver.
	 */
	class AssetManager {
	public:
		class TextureOptions {
		public:
			TextureOptions (bool smooth = false,
							bool mipmap = true,
							const IntRect &area = IntRect());
			bool smooth;
			bool mipmap;
			IntRect area;
		};

		AssetManager (StreamResolver &resolver);
		virtual ~AssetManager ();
		StreamResolver &getResolver () const;
		const Texture &loadTexture (const string &path, const TextureOptions &opt = TextureOptions());
		const SoundBuffer &loadSoundBuffer (const string &path);
		const Font &loadFont (const string &path);

	private:
		class FontAsset {
		public:
			FontAsset (const Font &font, const InputStream &stream);
			virtual ~FontAsset ();
			const Font *font;
			const InputStream *stream;
		};

		StreamResolver *_resolver;
		unordered_map<string, Texture*> _textures;
		unordered_map<string, SoundBuffer*> _soundBuffers;
		unordered_map<string, FontAsset*> _fonts;
	};
}

#endif
