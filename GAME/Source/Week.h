namespace game_framework
{
	

	class Week
	{
	public:
		Week();
		void LoadBitmap();		// 載入圖形
		void OnMove();			// 移動
		void OnShow();			// 將圖形貼到畫面
	private:
		int week_x, week_y;				// 圖形座標
		CAnimation week_animation;
	};
}
