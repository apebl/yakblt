/* assetmanager.hpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __YAKBLT_ASSETMANAGER_H__
#define __YAKBLT_ASSETMANAGER_H__

#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

namespace yakblt {
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
