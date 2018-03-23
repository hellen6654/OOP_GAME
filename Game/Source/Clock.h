namespace game_framework
{
////////////////////////////////
//      這個class提供時鐘     //
////////////////////////////////

class Clock
{
    public:
        Clock();
        void LoadBitmap();		// 載入圖形
        void OnMove();			// 移動
        void OnShow();			// 將圖形貼到畫面

    private:

        int x, y;				// 圖形座標
        CAnimation animation;	// 利用動畫作圖形
};
}