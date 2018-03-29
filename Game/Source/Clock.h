namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供會一直彈跳的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Clock
	{
	public:
		Clock();
		void LoadBitmap();		// 載入圖形
		void OnMove();			// 移動
		void OnShow();			// 將圖形貼到畫面
	private:
		int clk_x, clk_y,week_x,week_y;				// 圖形座標
		CAnimation clock_animation;	// 利用動畫作圖形
		CAnimation week_animation;
	};
}