/*
 This file is part of MMOServer. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2010 The SWG:ANH Team

 MMOServer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMOServer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMOServer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ANH_DATABASE_MOCK_CPPCONN_H_
#define ANH_DATABASE_MOCK_CPPCONN_H_

#include <turtle/mock.hpp>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/metadata.h>
#include <cppconn/parameter_metadata.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>

// Generate mock objects for the Mysql Connector/C++ interface.
namespace anh {
namespace database {

MOCK_BASE_CLASS( MockDriver, sql::Driver )
{
    MOCK_METHOD_EXT(connect, 3, sql::Connection*(const sql::SQLString&, const sql::SQLString&, const sql::SQLString&), connect3)
    MOCK_METHOD_EXT(connect, 1, sql::Connection*(sql::ConnectOptionsMap& options), connect1)
    MOCK_METHOD(getMajorVersion, 0)
    MOCK_METHOD(getMinorVersion, 0)
    MOCK_METHOD(getPatchVersion, 0)
    MOCK_METHOD(getName, 0)
    MOCK_METHOD(threadInit, 0)
    MOCK_METHOD(threadEnd, 0)
};

MOCK_BASE_CLASS(MockConnection, sql::Connection)
{
    MOCK_METHOD(clearWarnings, 0);
    MOCK_METHOD(createStatement,0);
    MOCK_METHOD(close, 0);
    MOCK_METHOD(commit, 0);
    MOCK_METHOD(getAutoCommit, 0);
    MOCK_METHOD(getCatalog, 0);
    MOCK_METHOD(getDriver, 0);
    MOCK_METHOD(getSchema, 0);
    MOCK_METHOD(getClientInfo, 0);
    MOCK_METHOD(getClientOption, 2);
    MOCK_METHOD(getMetaData, 0);
    MOCK_METHOD(getTransactionIsolation, 0);
    MOCK_METHOD(getWarnings, 0);
    MOCK_METHOD(isClosed, 0);
    MOCK_METHOD(isReadOnly, 0);
    MOCK_METHOD(nativeSQL, 1);
    MOCK_METHOD_EXT(prepareStatement, 1, sql::PreparedStatement*(const sql::SQLString& sql), tag1);
    MOCK_METHOD_EXT(prepareStatement, 2, sql::PreparedStatement*(const sql::SQLString& sql, int autoGeneratedKeys), tag2);
    MOCK_METHOD_EXT(prepareStatement, 2, sql::PreparedStatement*(const sql::SQLString& sql, int* columnIndexes), tag3);
    MOCK_METHOD_EXT(prepareStatement, 3, sql::PreparedStatement*(const sql::SQLString& sql, int resultSetType, int resultSetConcurrency), tag4);
    MOCK_METHOD_EXT(prepareStatement, 4, sql::PreparedStatement*(const sql::SQLString& sql, int resultSetType, int resultSetConcurrency, int resultSetHoldability), tag5);
    MOCK_METHOD_EXT(prepareStatement, 2, sql::PreparedStatement*(const sql::SQLString& sql, sql::SQLString columnNames[]), tag6);
    MOCK_METHOD(releaseSavepoint, 1);
    MOCK_METHOD_EXT(rollback, 0, void(), tag7);
    MOCK_METHOD_EXT(rollback, 1, void(sql::Savepoint *), tag8 );
    MOCK_METHOD(setAutoCommit, 1);
    MOCK_METHOD(setCatalog, 1);
    MOCK_METHOD(setSchema, 1);
    MOCK_METHOD(setClientOption, 2);
    MOCK_METHOD(setHoldability, 1);
    MOCK_METHOD(setReadOnly, 1);
    MOCK_METHOD_EXT(setSavepoint, 0, sql::Savepoint*(), tag9);
    MOCK_METHOD_EXT(setSavepoint, 1, sql::Savepoint*(const sql::SQLString&), tag10);
    MOCK_METHOD(setTransactionIsolation, 1);
};

MOCK_BASE_CLASS(MockStatement, sql::Statement)
{
    MOCK_METHOD(getConnection, 0);
    MOCK_METHOD(cancel, 0);
    MOCK_METHOD(clearWarnings, 0);
    MOCK_METHOD(close, 0);
    MOCK_METHOD(execute, 1);
    MOCK_METHOD(executeQuery, 1);
    MOCK_METHOD(executeUpdate, 1);
    MOCK_METHOD(getFetchSize, 0);
    MOCK_METHOD(getMaxFieldSize, 0);
    MOCK_METHOD(getMaxRows, 0);
    MOCK_METHOD(getMoreResults, 0);
    MOCK_METHOD(getQueryTimeout, 0);
    MOCK_METHOD(getResultSet, 0);
    MOCK_METHOD(getResultSetType, 0);
    MOCK_METHOD(getUpdateCount, 0);
    MOCK_METHOD(getWarnings, 0);
    MOCK_METHOD(setCursorName, 1);
    MOCK_METHOD(setEscapeProcessing, 1);
    MOCK_METHOD(setFetchSize, 1);
    MOCK_METHOD(setMaxFieldSize, 1);
    MOCK_METHOD(setMaxRows, 1);
    MOCK_METHOD(setQueryTimeout, 1);
    MOCK_METHOD(setResultSetType, 1);
};

MOCK_BASE_CLASS(MockPreparedStatement, sql::PreparedStatement)
{
    MOCK_METHOD(clearParameters, 0);
    MOCK_METHOD_EXT(execute, 1, bool(const sql::SQLString& sql), tag1);
    MOCK_METHOD_EXT(execute, 0, bool(), tag2);
    MOCK_METHOD_EXT(executeQuery, 1, sql::ResultSet*(const sql::SQLString& sql), tag3);
    MOCK_METHOD_EXT(executeQuery, 0, sql::ResultSet*(), tag4);
    MOCK_METHOD_EXT(executeUpdate, 1, int(const sql::SQLString& sql), tag5);
    MOCK_METHOD_EXT(executeUpdate, 0, int(), tag6);
    MOCK_METHOD(getMetaData, 0);
    MOCK_METHOD(getParameterMetaData, 0);
    MOCK_METHOD(setBigInt, 2);
    MOCK_METHOD(setBlob, 2);
    MOCK_METHOD(setBoolean, 2);
    MOCK_METHOD(setDateTime, 2);
    MOCK_METHOD(setDouble, 2);
    MOCK_METHOD(setInt, 2);
    MOCK_METHOD(setUInt, 2);
    MOCK_METHOD(setInt64, 2);
    MOCK_METHOD(setUInt64, 2);
    MOCK_METHOD(setNull, 2);
    MOCK_METHOD(setString, 2);
    MOCK_METHOD(setResultSetType, 1);
};

MOCK_BASE_CLASS(MockResultSet, sql::ResultSet)
{
    MOCK_METHOD(absolute, 1);
    MOCK_METHOD(afterLast, 0);
    MOCK_METHOD(beforeFirst, 0);
    MOCK_METHOD(cancelRowUpdates, 0);
    MOCK_METHOD(clearWarnings, 0);
    MOCK_METHOD(close, 0);
    MOCK_CONST_METHOD_EXT(findColumn, 1, uint32_t(const sql::SQLString& columnLabel), tag1);
    MOCK_METHOD(first, 0);
    MOCK_CONST_METHOD_EXT(getBlob, 1, std::istream*(uint32_t columnIndex), tag2);
    MOCK_CONST_METHOD_EXT(getBlob, 1, std::istream*(const sql::SQLString& columnLabel), tag3);
    MOCK_CONST_METHOD_EXT(getBoolean, 1, bool(uint32_t columnIndex), tag4);
    MOCK_CONST_METHOD_EXT(getBoolean, 1, bool(const sql::SQLString& columnLabel), tag5);
    MOCK_METHOD(getConcurrency, 0);
    MOCK_METHOD(getCursorName, 0);
    MOCK_CONST_METHOD_EXT(getDouble, 1, long double(uint32_t columnIndex), tag6);
    MOCK_CONST_METHOD_EXT(getDouble, 1, long double(const sql::SQLString& columnLabel), tag7);
    MOCK_METHOD(getFetchDirection, 0);
    MOCK_METHOD(getFetchSize, 0);
    MOCK_METHOD(getHoldability, 0);
    MOCK_CONST_METHOD_EXT(getInt, 1, int32_t(uint32_t columnIndex), tag8);
    MOCK_CONST_METHOD_EXT(getInt, 1, int32_t(const sql::SQLString& columnLabel), tag9);
    MOCK_CONST_METHOD_EXT(getUInt, 1, uint32_t(uint32_t columnIndex), tag10);
    MOCK_CONST_METHOD_EXT(getUInt, 1, uint32_t(const sql::SQLString& columnLabel), tag11);
    MOCK_CONST_METHOD_EXT(getInt64, 1, int64_t(uint32_t columnIndex), tag12);
    MOCK_CONST_METHOD_EXT(getInt64, 1, int64_t(const sql::SQLString& columnLabel), tag13);
    MOCK_CONST_METHOD_EXT(getUInt64, 1, uint64_t(uint32_t columnIndex), tag14);
    MOCK_CONST_METHOD_EXT(getUInt64, 1, uint64_t(const sql::SQLString& columnLabel), tag15);
    MOCK_CONST_METHOD_EXT(getMetaData, 0, sql::ResultSetMetaData*(), tag16);
    MOCK_CONST_METHOD_EXT(getRow, 0, size_t(), tag17);
    MOCK_METHOD_EXT(getRowId, 1, sql::RowID*(uint32_t columnIndex), tag18);
    MOCK_METHOD_EXT(getRowId, 1, sql::RowID*(const sql::SQLString& columnLabel), tag19);
    MOCK_CONST_METHOD_EXT(getStatement, 0, const sql::Statement*(), tag20);
    MOCK_CONST_METHOD_EXT(getString, 1, sql::SQLString(uint32_t columnIndex), tag21);
    MOCK_CONST_METHOD_EXT(getString, 1, sql::SQLString(const sql::SQLString& columnLabel), tag22);
    MOCK_CONST_METHOD_EXT(getType, 0, sql::ResultSet::enum_type(), tag23);
    MOCK_METHOD(getWarnings, 0);
    MOCK_METHOD(insertRow, 0);
    MOCK_CONST_METHOD_EXT(isAfterLast, 0, bool(), tag24);
    MOCK_CONST_METHOD_EXT(isBeforeFirst, 0, bool(), tag25);
    MOCK_CONST_METHOD_EXT(isClosed, 0, bool(), tag26);
    MOCK_CONST_METHOD_EXT(isFirst,0,  bool(), tag27);
    MOCK_CONST_METHOD_EXT(isLast, 0, bool(), tag28);
    MOCK_CONST_METHOD_EXT(isNull, 1,  bool(uint32_t columnIndex), tag29);
    MOCK_CONST_METHOD_EXT(isNull, 1, bool(const sql::SQLString& columnLabel), tag30);
    MOCK_METHOD(last, 0);
    MOCK_METHOD(next, 0);
    MOCK_METHOD(moveToCurrentRow, 0);
    MOCK_METHOD(moveToInsertRow, 0);
    MOCK_METHOD(previous, 0);
    MOCK_METHOD(refreshRow, 0);
    MOCK_METHOD(relative, 1);
    MOCK_METHOD(rowDeleted, 0);
    MOCK_METHOD(rowInserted, 0);
    MOCK_METHOD(rowUpdated, 0);
    MOCK_METHOD(setFetchSize, 1);
    MOCK_CONST_METHOD_EXT(rowsCount, 0, size_t(), tag31);
    MOCK_CONST_METHOD_EXT(wasNull, 0, bool(), tag32);
};

}  // namespace database
}  // namespace anh

#endif  // ANH_DATABASE_MOCK_CPPCONN_H_
