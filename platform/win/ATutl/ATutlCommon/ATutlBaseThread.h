#ifndef __ATUTLBASETHREAD_H__84CF87E1_0AB6_49C8_A1A5_26A31D0C55DA
#define __ATUTLBASETHREAD_H__84CF87E1_0AB6_49C8_A1A5_26A31D0C55DA

/**
 * スレッド基底クラス<br>
 * <b>ATutlBaseThread.h</b>
 *
 * @author slowhand0309
 */
class ATBaseThread
{
public:

	/**
	 * コンストラクタ
	 */
	ATBaseThread();

	/**
	 * デストラクタ
	 */
	virtual ~ATBaseThread();

	/**
	 * 初期化処理
	 *
	 * @return	int
	 */
	virtual int initialize();

	/**
	 * 終了処理
	 */
	virtual void finalize();

	/**
	 * スレッド開始
	 *
	 * @param int	nPriority		優先度
	 */
	virtual int startThread(int	nPriority);

	/**
	 * スレッド実行処理
	 * 
	 * @param LPVOID pParam			this
	 */
	virtual int run(LPVOID pParam) = 0;

protected:
	/**
	 * スレッド内で実行される関数
	 */
	static UINT	l_ThreadFunc(LPVOID pParam);

	CWinThread *			ml_pThread;
};
#endif // __ATUTLBASETHREAD_H__84CF87E1_0AB6_49C8_A1A5_26A31D0C55DA