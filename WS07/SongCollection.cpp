#include "SongCollection.h"

namespace sdds
{
	void SongCollection::trim(std::string& src)
	{
		if (!src.empty() && src.length() > 1)
		{
			size_t begin = src.find_first_not_of(' ');
			size_t end = src.find_last_not_of(' ');
			src = src.substr(begin, (end - begin + 1));
		}
	}

	SongCollection::SongCollection(const std::string filename)
	{
		std::string temp;
		Song temp_song;

		std::ifstream file(filename);
		if (!file)
		{
			std::string err = "ERROR: Cannot open file [" + filename + "]";
			throw err;
		}
		
		while (!file.eof())
		{
			std::getline(file, temp);

			temp_song.m_title = temp.substr(0, 25);
			trim(temp_song.m_title);
			temp.erase(0, 25);

			temp_song.m_artist = temp.substr(0, 25);
			trim(temp_song.m_artist);
			temp.erase(0, 25);

			temp_song.m_album = temp.substr(0, 25);
			trim(temp_song.m_album);
			temp.erase(0, 25);

			try //check for a valid year
			{
				temp_song.m_year = std::stoi(temp.substr(0, 5));
			}
			catch (...)
			{
				temp_song.m_year = -1;
			}		
			temp.erase(0, 5);

			//to convert string to size_t
			std::stringstream len(temp.substr(0, 5));
			len >> temp_song.m_songLen;
			temp.erase(0, 5);

			temp_song.m_price = std::stod(temp.substr(0, 5));

			m_songs.push_back(temp_song);
		}
		m_totalPlaytime = std::accumulate(m_songs.begin(), m_songs.end(), (size_t)0,
			[](size_t len, const Song& song) {return len + song.m_songLen;});
	}

	void SongCollection::sort(const std::string sortBy)
	{
		//capture sortBy by value
		std::sort(m_songs.begin(), m_songs.end(), [=](const Song& song1, const Song& song2)
			{
				if (sortBy == "artist")
				{
					return song1.m_artist < song2.m_artist;
				}
				else if (sortBy == "title")
				{
					return song1.m_title < song2.m_title;
				}
				else {
					return song1.m_songLen < song2.m_songLen;
				}
			});
	}

	void SongCollection::display(std::ostream& out) const
	{
		std::for_each(m_songs.begin(), m_songs.end(), [&out](const Song& m_songs) {
			out << m_songs << std::endl; });

		size_t hour = m_totalPlaytime / 3600;
		size_t min = (m_totalPlaytime % 3600) / 60;
		size_t sec = (m_totalPlaytime % 3600) % 60;

		out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ') << "| " << std::setfill(' ') << std::setw(76) << std::right << "Total Listening Time:"
			<< std::setw(2) << hour << ":" << std::setw(2) << std::setfill('0') << min 
			<< ":" << std::setw(2) << std::setfill('0') << sec << " |" << std::endl;
	}

	void SongCollection::cleanAlbum()
	{
		std::transform(m_songs.begin(), m_songs.end(), m_songs.begin(), 
			[](Song& song) {
				if ((song.m_album == "[None]"))
				{
					song.m_album = " ";
				}
				return song;
			});
	}

	bool SongCollection::inCollection(std::string artist) const
	{
		// capture artist by value
		return std::any_of(m_songs.begin(), m_songs.end(), [=](const Song& song) {
			return song.m_artist == artist; });
	}

	std::list<Song> SongCollection::getSongsForArtist(std::string artist) const
	{
		std::list<Song> collection;

		std::copy_if(m_songs.begin(), m_songs.end(), std::back_inserter(collection), 
			[=](const Song& song) { return song.m_artist == artist; });

		return collection;
	}

	std::ostream& operator<<(std::ostream& out, const Song& theSong)
	{
		out << "| " << std::setfill(' ') << std::setw(20) << std::left << theSong.m_title
			<< " | " << std::setw(15) << theSong.m_artist
			<< " | " << std::setw(20) << theSong.m_album;
		if (theSong.m_year != -1)
		{
			out << " | " << std::setw(6) << std::right << theSong.m_year;
		}
		else {
			out << " | " << std::setw(6) << std::right << " ";
		}
		out << " | " << theSong.m_songLen / 60
			<< ":" << std::setw(2) << std::setfill('0') << theSong.m_songLen % 60 << " | "
			<< std::fixed << std::setprecision(2) << theSong.m_price << " |";
		return out;
	}
}