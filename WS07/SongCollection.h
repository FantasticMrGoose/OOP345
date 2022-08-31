#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <numeric>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#ifndef SDDS_SONGCOLLECTION_H
#define SDDS_SONGCOLLECTION_H

namespace sdds
{
	struct Song
	{
		std::string m_artist{};
		std::string m_title{};
		std::string m_album{};
		double m_price = 0;
		int m_year = 0;
		size_t m_songLen = 0;
	};

	class SongCollection
	{
		std::vector<Song> m_songs{};
		size_t m_totalPlaytime = 0;
		void trim(std::string& src);
	public:
		SongCollection() {};
		SongCollection(const std::string filename);
		void sort(const std::string sortBy);
		void cleanAlbum();
		bool inCollection(std::string artist) const;
		std::list<Song> getSongsForArtist(std::string artist) const; 
		void display(std::ostream& out) const;
	};

	std::ostream& operator<<(std::ostream& out, const Song& theSong);

}

#endif // !SDDS_SONGCOLLECTION_H
