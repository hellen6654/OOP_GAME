namespace game_framework
{
	 // http://www.programmer-club.com.tw/ShowSameTitleN/c/41191.html 
	 // https://www.ptt.cc/bbs/C_and_CPP/M.1312545686.A.A90.html
	class Map
	{
	public:
		Map();
		~Map();
		void LoadBmpData();
		void LoadBitmap();
		void ShowBitmap();
	private: 
		int rgb_data[800][600][3];
	};
}
