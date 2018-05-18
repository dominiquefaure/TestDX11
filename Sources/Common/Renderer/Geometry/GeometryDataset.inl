
//---------------------------------------------------------------------------------------------------------
FORCE_INLINE RhiPrimitiveType GeometryDataset::GetPrimitiveType()const
{
	return m_primitiveType;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TBool GeometryDataset::IsIndexed()const
{
	return m_isIndexed;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TUint32 GeometryDataset::GetIndiceCount()const
{
	return m_indexCount;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE RhiIndexBufferType GeometryDataset::GetIndexBufferType()const
{
	return m_indexType;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE void* GeometryDataset::GetIndexBuffer()const
{
	if( m_indexType == INDEX_BUFFER_TYPE_16 )
	{
		return m_indexBuffer16;
		
	}

	return m_indexBuffer32;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE RhiVertexLayoutType GeometryDataset::GetVerticeType()const
{
	return m_vertexLayoutType;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TUint32 GeometryDataset::GetVerticeCount()const
{
	return m_vertexCount;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TUint32 GeometryDataset::GetVerticeSize()const
{
	return m_vertexSize;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat32* GeometryDataset::GetVertexBuffer()const
{
	return m_vertexBuffer;	
}
//---------------------------------------------------------------------------------------------------------
