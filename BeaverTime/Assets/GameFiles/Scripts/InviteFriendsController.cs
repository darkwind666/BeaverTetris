using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Tacticsoft;
using com.playGenesis.VkUnityPlugin;


public class InviteFriendsController : MonoBehaviour, ITableViewDataSource {

	public VKFriendCell m_cellPrefab;
	public TableView m_tableView;

	public List<VKUser> friendsDataSource;

	void Start () {
		m_tableView.dataSource = this;
		if(friendsDataSource == null)
		{
			friendsDataSource = new List<VKUser>();
		}
	}

	void Update () {
	
	}

	void OnEnable()
	{
		if(friendsDataSource != null && m_tableView.dataSource != null)
		{
			m_tableView.ReloadData();
		}
	}

	#region ITableViewDataSource

	public int GetNumberOfRowsForTableView(TableView tableView) {
		return friendsDataSource.Count;
	}

	//Will be called by the TableView to know what is the height of each row
	public float GetHeightForRowInTableView(TableView tableView, int row) {
		return (m_cellPrefab.transform as RectTransform).rect.height;
	}

	//Will be called by the TableView when a cell needs to be created for display
	public TableViewCell GetCellForRowInTableView(TableView tableView, int row) {
		VKFriendCell cell = tableView.GetReusableCell(m_cellPrefab.reuseIdentifier) as VKFriendCell;
		if (cell == null) {
			cell = (VKFriendCell)GameObject.Instantiate(m_cellPrefab);
		}
		VKUser cellData = friendsDataSource[row];
		cell.friendName.text = cellData.first_name + " " + cellData.last_name;
		return cell;
	}

	#endregion


}
