namespace game_framework
{
	class Passenger
	{
	public:
		Passenger();
		void LoadBitmap();			//���J�ϧ�
		void SetType(int);
		void SetXY(int,int);

		int GetStartStation();
		void RandomMadePassenger(vector<Passenger>&,int,int);
		void RandomMadePassenger(int);
		void OnShow();				//�N�ϧζK��e��
		~Passenger();
	private:
		CMovingBitmap passengerAnimation;					//�Q�ΰʵe�@�ϧ�
		const int MAXIUM_PASSENGER_TYPE = 1;				//���ȼ˦��Ӽ�
		const int MAXIUM_PASSANGER = 20;
		int finalStation;									//�ت��a
		int startStation;									//�_�I
		int x, y;											//�ϧήy��
		int passengerType;									//��������
		vector<Passenger> passengerList;
	};
}

