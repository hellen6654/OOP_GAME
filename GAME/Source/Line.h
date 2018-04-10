

namespace game_framework
{
	class Line
	{
	public:
		Line();
		~Line();
		void SetmouseClickedPointA(int, int);
		void SetisStation_A_Clicked(bool);
		void SetisStation_B_Clicked(bool);
		void SetclickedStationNumA(int);
		void SetclickedStationNumB(int);
		int	 GetclickedStationNumA();
		int	 GetclickedStationNumB();
		int	 GetmouseClickedPoint_X();
		int	 GetmouseClickedPoint_Y();
		bool IsStation_A_Clicked();
		bool IsStation_B_Clicked();
		bool IsClickedOnStation(int,int,vector<Station>,int); //�ˬd�O�_���I�쨮��
	private:
		const int stationSize = 25;					// �C�i�������j�p��25*25
		int		mouseClickedPoint_X;				// �s��ƹ��I����m
		int		mouseClickedPoint_Y;				// �s��ƹ��I����m
		int		clickedStationNumA;					// ���ӬO�_�I����
		int		clickedStationNumB;					// ���ӬO���I����
		bool	isStation_A_Clicked;				// �O�_��X�_�I����
		bool	isStation_B_Clicked;				// �O�_��X���I����
	};

	
}