# API

### Log in
**From client to server request**
**Answer: RQ_TOKEN**
```
{
    "type": RQ_LOG_IN,
    "login": "user_login",
    "pass": "SHA-256 hash",
    "name": "user`s name",
    "desc": "user`s description"
}
```
**Nothing to client request**
### Sign up
**From client to server request**
**Answer: RQ_TOKEN**
```
{
    "type": RQ_SIGN_UP,
    "login": "user_login",
    "pass": "SHA-256 hash",
    "name": "user`s name",
    "desc": "user`s description"
}
```
**Nothing to client request**
### Log in by token
**From client to server request**
**Answer: RQ_TOKEN**
```
{
    "type": RQ_TOKEN,
    "token": "SHA-256 token"
}
```
**From server to client request**
```
{
    "type": RQ_TOKEN,
    "token": "SHA-256 token"
    "login": "user_login",
    "desc": "user`s description"
}
```
### Message
**From client to server request**
**Answer: RQ_MSG to every online member in room**
```
{
    "type": RQ_MSG,
    "room_id": room_id,
    "message": "message",
    "msg_type" DB_TEXT_MSG
}
```
**From server to client request**
```
{
    "type": RQ_MSG,
    "room_id": room_id,
    "message": "message",
    "date": date,
    "message_id", message_id_in_database,
    "user_id", user_id_that_wrote_message,
    "msg_type" DB_TEXT_MSG(DB_STICKER ...)
}
```
### Error message
**Nothing from client to server request**
**From server to client request**
```
{
   "type": RQ_ERROR_MSG,
   "error_code": ER_USER_EXST(ER_AUTH_DATA ...),
   "msg": "error message"
}
```
### Edit message
**From client to server request**
**Answer: RQ_EDIT_MSG to every online member in room**
```
{
    "type": RQ_EDIT_MSG,
    "room_id": room_id_that_contains_message,
    "msg_id": message_id_that_need_to_edit,
    "msg": "edited_message"
}
```
**From server to client request**
```
{
    "type": RQ_EDIT_MSG,
    "room_id": room_id_that_contains_message,
    "msg_id": message_id_that_need_to_edit,
    "msg": "edited_message"
}
```
### Delete message
**From client to server request**
**Answer: RQ_DEL_MSG to every online member in room**
```
{
    "type": RQ_DEL_MSG,
    "room_id": room_id_that_contains_message,
    "msg_id": message_id_that_need_to_delete
}
```
**From server to client**
```
{
    "type": RQ_DEL_MSG,
    "room_id": room_id_that_contains_message,
    "msg_id": message_id_that_need_to_delete
}
```
### Delete chat-history of room
**From client to server request**
**Answer: RQ_DEL_HIST to every online member in room**
```
{
    "type": RQ_DEL_HIST,
    "room_id": room_id_that_need_to_clear
}
```
**From server to client request**
```
{
    "type": RQ_DEL_HIST,
    "room_id": room_id_that_need_to_clear
}
```
### Get new messages
**From client to server request**
**Answer: RQ_GET_NEW_MSGS**
```
{
    "type": RQ_GET_NEW_MSGS,
    "date": date,
    "room_id": room_id,
    "count": messages_count
}
```
**From server to client request**
```
{
   "type": RQ_GET_NEW_MSGS,
   "room_id": room_id,
   "messages": [{ /*array of message*/
   }]
}
```
### Search messages
**From client to server request**
**Answer: RQ_SEARCH_MSGS**
```
{
    "type": RQ_SEARCH_MSGS,
    "msg": "start_of_message_that_need_to_find",
    "room_id": room_id_where_need_to_find_messages
}
```
**From server to client request**
```
{
   "type": RQ_SEARCH_MSGS
   "msgs": [{ /*array of message*/
   }]
}
```
### Get old messages
**From client to server request**
**Answer: RQ_OLD_MSGS**
```
{
    "type": RQ_OLD_MSGS,
    "date": date,
    "room_id": room_id,
    "count": messages_count
}
```
**From server to client request**
```
{
    "type": RQ_OLD_MSGS,
    "room_id": room_id,
    "message": [{ /*array of message*/
    }]
}
```
### Get rooms
**From client to server request**
**Answer: RQ_GET_ROOMS**
```
{
    "type": RQ_GET_ROOMS,
    "date": date
}
```
**From server to client request**
```
{
    "type": RQ_GET_ROOMS,
    "rooms": [{ /*array of rooms*/
    }]
}
```
### Create new room
**From client to server request**
**Answer: RQ_NEW_ROOM**
```
{
   "type": RQ_NEW_ROOM,
   "name": "room name",
   "desc": "room description",
   "type": room_type
}
```
**From server to client request**
```
{
    "type": RQ_NEW_ROOM,
    "name": "room name",
    "customer_id": customer_id,
    "id": room_id,
    "date", creation_date,
    "desc", "room description"
}
```
### Delete room
**From client to server request**
**Answer: RQ_DEL_ROOM to every online member in room**
```
{
    "type": RQ_DEL_ROOM,
    "room_id": room_id
}
```
**From server to client request**
```
{
    "type": RQ_DEL_ROOM,
    "room_id": room_id
}
```
### Join to room
**From client to server request**
**Answer: RQ_NEW_MEMBER to every online member in room and RQ_JOIN_ROOM to sender**
```
{
    "type": RQ_JOIN_ROOM,
    "room_id": room_id
}
```
**From server to client request**
```
{
    "type": RQ_NEW_MEMBER,
    "room_id": room_id,
    "user_id": user_id,
    "login": "user login"
}
```
```
{
   "type": RQ_JOIN_ROOM,
   "name": "room name",
   "customer_id": customer_id,
   "id": room_id,
   "date": creation_date,
   "desc": "room description"
}
```
### Update room name
**From client to server request**
**Answer: RQ_UPD_ROOM_NAME to every online member in room**
```
{
    "type": RQ_UPD_ROOM_NAME,
    "room_id": room_id,
    "room_name": "new room name"
}
```
**From server to client request**
```
{
    "type": RQ_UPD_ROOM_NAME,
    "room_id": room_id,
    "room_name": "new room name"
}
```
### Update room description
**From client to server request**
**Answer: RQ_UPD_ROOM_DESC to every online member in room**
```
{
    "type": RQ_UPD_ROOM_DESC,
    "room_id": room_id,
    "desc": "new room description"
}
```
**From server to client request**
```
{
    "type": RQ_UPD_ROOM_DESC,
    "room_id": room_id,
    "desc": "new room description"
}
```
### Search room
**From client to server request**
**Answer: RQ_SEARCH_CH**
```
{
    "type": RQ_SEARCH_CH,
    "name": "start_of_room_name"
}
```
**From server to client request**
```
{
    "type": RQ_SEARCH_CH,
    "rooms": [{ /*array of rooms*/
    }]
}
```
### Get members
**From client to server request**
**Answer: RQ_GET_MEMBERS**
```
{
    "type": RQ_GET_MEMBERS,
    "room_id": room_id
}
```
**From server to client request**
```
{
    "type": RQ_SEARCH_CH,
    "room_id": room_id,
    "members": [{ /*array of members*/
    }]
}
```
### Get information about member
**From client to server request**
**Answer: RQ_MEMBER_INFO**
```
{
    "type": RQ_MEMBER_INFO,
    "user_id": member_id
}
```
**From server to client request**
```
{
    "type": RQ_MEMBER_INFO,
    "desc": "member description",
    "login": "member login"
}
```
### New member in room
**Nothing from client to server request**
**From server to client request**
```
{
   "type": RQ_NEW_MEMBER,
   "user_id": member_id,
   "room_id": room_id,
   "login": "member login"
}
```
### Ban member in room
**From client to server request**
**Answer: RQ_BAN_MEMBER to every online member in room**
```
{
   "type": RQ_BAN_MEMBER,
   "room_id": room_id,
   "user_id": member_to_ban_id
}
```
**From server to client request**
```
{
   "type": RQ_BAN_MEMBER,
   "room_id": room_id,
   "user_id": banned_member_id
}
```
### Update user description
**From client to server request**
**Answer: RQ_UPD_USER_DESC**
```
{
   "type": RQ_UPD_USER_DESC,
   "desc": "new user description"
}
```
**From server to client request**
```
{
   "type": RQ_UPD_USER_DESC,
   "desc": "new user description"
}
```
### Upload file to server
**From client to server request**
**Answer: nothing. Server is uploading file**
```
{
   "type": RQ_UPLOAD_FILE,
   "name": "filename",
   "size": file_size,
   "room_id": room_id,
   "token": "SHA-256 user token"
}
```
### Download file to server
**From client to server request**
**Answer: RQ_DOWNLOAD_FILE**
```
{
   "type": RQ_DOWNLOAD_FILE,
   "room_id": room_id,
   "msg_id": message_id_that_contains_file,
   "token": "SHA-256 user token"
}
```
**From server to client request**
```
{
   "type": RQ_DOWNLOAD_FILE,
   "size": file_size,
   "name": "file name"
}
```
### Log out
**From client to server request**
**Answer: RQ_LOG_OUT**
```
{
   "type": RQ_LOG_OUT,
   "token": "SHA-256 user token"
}
```
**From server to client request**
```
{
   "type": RQ_LOG_OUT,
   "token": "SHA-256 user token"
}
```
