�}�6  �  'i ��l&�����71���S�����y[=y�٣z�A�d�����g�n�S�nKN��Ԭ��VC�3��C�j7��A�~h��Pz>~7�S0ߗ�_��z��]mժY)�+~�*P㶶G�P��"J��6 �h0ӏ_�[J��������A*]	9[Ħ�T+��p����ѾTN������	�H69T��O�v-�=�갽L���N��,d��UT�\����<���&	dOz�%4�w��}���ci#��������e��Z}d�s%�fPb�~�b%z�������a��x� �}MnG> ��ZD��ח���Mx�O����6�f2�ux �|�=\��r�}I��Q���$/}�/q�\*�@L䑟 
)P3g+ú8�0�ƃ ��^*?<0=�"���2� �	 :�zp̖� !e��5�b+��z���|5�,J3�x �3{�����F��k�\��xI�M f`�r�Ga��[����A,t۴治���ڶ�������ifExists = 0��ʾ������������򴴽��������򷵻ش���
	//����֮���Զ�ת��������ݿ�
	CDataBase* CreateDataBase(CString NewdbName,bool ifExists = 1);
	//�������ݿ⣬ͬʱ�ͷ�pDataBase�ռ�
	int DropDataBase(CDataBase *pDataBase);
	//����Ҫ���������ݿ�
	CDataBase* OpenDataBaseInterface(CString dbName);
	//�ر����ݿ�
	void CloseDataBaseInterface(CDataBase *pDataBase);
};