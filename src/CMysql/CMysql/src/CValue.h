�}U6  �  �e�B�%�����>1���S�����y[=y�٣z�A�d�����g��>�̘�_���Ckp����r17�����4S�<��!��=��ьf�����g��-Q/���K���p�[D��I5.+��zmj�8��腻�#]廂����~¯W���'�k	�kћ(��:kDM)�q�}g{hﺊ~R!�p��K���]k�^�K�����2OM:���?A�JEJ���$�F��P$�wߦȟ�&�TEr�K���wl��@v��,T>��Ҩ��
��9WF@O2��m�:8T��TEٮM���F`/���g'�'���Lv�Q�GO#vH�6�f2�ux �|�=\��r�}I��Q���$/}�/q�\*�@L䑟 
)P3g+ú8�0�ƃ ��^*?<0=�"���2� �	 :�zp̖� !e��5�b+��z���|5�,J3�x �3{�����F��k�\��xI�M f`�r�Ga��[����A,t;
	CValue(BOOL Type,CString strValue,int nValue,double dValue);

	CValue(const CValue& value);
	CValue operator= (const CValue& value);
	bool operator== (const CValue& value);
	bool operator!= (const CValue& value);

	operator int();
	operator CString();
	operator double();

public:
	//���Ҫ���̲߳����Ļ���Ҫ��init����ʹ��CValue
	//void init(CTable* pTable);

public:
	//CAttri* operator->();
};