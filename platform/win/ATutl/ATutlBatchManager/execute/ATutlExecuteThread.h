#ifndef __ATUTLEXECUTETHREAD_H__037950AA_461F_48BB_B391_4651BAF09500
#define __ATUTLEXECUTETHREAD_H__037950AA_461F_48BB_B391_4651BAF09500

class ATExecuteThread : public ATBaseThread
{
public:

	/**
	 * コンストラクタ
	 */
	ATExecuteThread();

	/**
	 * デストラクタ
	 */
	virtual ~ATExecuteThread();

	/**
	 * 実行パスの設定
	 *
	 * @param	const TString &szCmdLine	実行パス 
	 */
	void setCmdLine(const TString &szCmdLine);

	/**
	 * 通知先CEditの設定
	 *
	 * @param	CEdit *pEdit				通知先
	 */
	void setNotifyEdit(CEdit *pEdit);

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
	 * スレッド実行処理
	 * 
	 * @param LPVOID pParam			this
	 */
	virtual int run(LPVOID pParam);

	/**
	 * 実行プロセスの終了
	 */
	void stopProccess();

	/**
	 * 実行プロセスの強制終了
	 */
	void haltProcess();

protected:

	int execute();

	/**
	 * 実行結果通知
	 */
	void notifyExecuteResult();

	/**
	 * 指定文字列をCEditへ通知
	 */
	void notifyWindow(const TString &szMessage);

	HANDLE					ml_hStdOut;						// 標準出力ハンドル
	HANDLE					ml_hReadStdOut;					// 標準出力読み込みハンドル
	HANDLE					ml_hProcHandle;
	TString					ml_szCmdLine;
	CEdit *					ml_pEdit;
};
#endif // __ATUTLEXECUTETHREAD_H__037950AA_461F_48BB_B391_4651BAF09500