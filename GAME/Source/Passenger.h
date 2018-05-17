namespace game_framework
{
	class Station;
	class Passenger
	{
	public:
		Passenger();
		Passenger(int,int,int,int,int);
		void LoadBitmap();									//���J�ϧ�
		void SetType(int);
		void SetXY(int,int);
		int GetStartStation();
		int GetFinalStation();
		void RandomMadePassenger(vector<Passenger>& passengerList,vector<Station> stationList, int stationMaxium, int stationTypeNum,int passenagerNum);
		void OnShow();										//�N�ϧζK��e��
		~Passenger();
	private:
		CMovingBitmap passengerAnimation;					//���ȹϧ� 
		int finalStation;									//���I
		int startStation;									//�_�I
		int x, y;											//�ϧήy��
		int passengerType;									//��������
	};
}

